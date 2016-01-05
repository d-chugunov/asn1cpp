#undef	NDEBUG
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>	/* for chdir(2) */
#include <string.h>
#include <dirent.h>
#include <assert.h>
#include <errno.h>
#include <iostream>
#include <memory>

#ifdef SINGLE_UNIT
#include <asn.hpp>
#else
#include <T.hpp>
#endif

using namespace ModuleTestANYSyntax;

enum expectation {
	EXP_OK,		/* Encoding/decoding must succeed */
	EXP_BROKEN,	/* Decoding must fail */
	EXP_RECLESS,	/* Reconstruction is allowed to yield less data */
	EXP_DIFFERENT,	/* Reconstruction will yield different encoding */
};

std::vector<uint8_t> buf;

static int
save_object(T *st) {
	asn_enc_rval_t rval; /* Return value */

  rval = st->EncodeDer(buf);
	if (rval.encoded == -1) {
		fprintf(stderr,
			"Cannot encode %s: %s\n",
			rval.failed_type->name, strerror(errno));
		assert(rval.encoded != -1);
		return -1;	/* JIC */
	}

	fprintf(stderr, "SAVED OBJECT IN SIZE %d\n", buf.size());

	return 0;
}

static std::unique_ptr<T>
load_object(enum expectation expectation, unsigned char *fbuf, size_t size) {
	asn_dec_rval_t rval;
	std::unique_ptr<T> st;
	int csize;
  
	fprintf(stderr, "LOADING OBJECT OF SIZE %d\n", (int)size);

	/* Perform multiple iterations with multiple chunks sizes */
	for(csize = 1; csize < 20; csize += 1) {
		int fbuf_offset = 0;
		int fbuf_left = size;
		int fbuf_chunk = csize;


		do {
			fprintf(stderr, "Decoding from %d with %d (left %d)\n",
				fbuf_offset, fbuf_chunk, fbuf_left);
      if (!st)
        st.reset(new T());
      rval = st->DecodeBer(fbuf + fbuf_offset, 
              fbuf_chunk < fbuf_left 
						? fbuf_chunk : fbuf_left);
			fbuf_offset += rval.consumed;
			fbuf_left -= rval.consumed;
			if(rval.code == RC_WMORE)
				fbuf_chunk += 1;	/* Give little more */
			else
				fbuf_chunk = csize;	/* Back off */
		} while(fbuf_left && rval.code == RC_WMORE);

		if(expectation != EXP_BROKEN) {
			assert(rval.code == RC_OK);
			assert(fbuf_offset == (ssize_t)size);
		} else {
			assert(rval.code != RC_OK);
			fprintf(stderr, "Failed, but this was expected\n");
			st.reset();
		}
	}

	if(st) st->Print(std::cerr);
	return st;
}


static void
process_data(enum expectation expectation, unsigned char *fbuf, ssize_t size) {
	std::unique_ptr<T> st;
	int ret;

	st = load_object(expectation, fbuf, size);
	if(!st) return;

	ret = save_object(st.get());
	assert(ret == 0);

	switch(expectation) {
	case EXP_RECLESS:
		assert(buf.size() > 0 && buf.size() < size);
		assert(memcmp(buf.data() + 2, fbuf + 2, buf.size() - 2) == 0);
		break;
	case EXP_DIFFERENT:
		assert(buf.size() > 0 && buf.size() < size);
		break;
	case EXP_BROKEN:
		assert(buf.size() != size
			|| memcmp(buf.data(), fbuf, buf.size()));
		break;
	case EXP_OK:
		assert(buf.size() == (ssize_t)size);
		assert(memcmp(buf.data(), fbuf, buf.size()) == 0);
		break;
	}
}

/*
 * Decode the .der files and try to regenerate them.
 */
static int
process(const char *fname) {
	unsigned char fbuf[4096];
	const char *ext = strrchr(fname, '.');
	enum expectation expectation;
	int ret;
	int rd;
	FILE *fp;

	if(ext == 0 || strcmp(ext, ".ber"))
		return 0;

	switch(ext[-1]) {
	case 'B':	/* The file is intentionally broken */
		expectation = EXP_BROKEN; break;
	case 'D':	/* Reconstructing should yield different data */
		expectation = EXP_DIFFERENT; break;
	case 'L':	/* Extensions are present */
		expectation = EXP_RECLESS; break;
	default:
		expectation = EXP_OK; break;
	}

	fprintf(stderr, "\nProcessing file [../%s]\n", fname);

	//ret = chdir("../data-62");
	//assert(ret == 0);
	std::string filepath = "../data-62/" + std::string(fname);
	fp = fopen(filepath.c_str(), "r");
	//ret = chdir("../test-check-62");
	//assert(ret == 0);
	assert(fp);

	rd = fread(fbuf, 1, sizeof(fbuf), fp);
	fclose(fp);

	assert(rd < (ssize_t)sizeof(fbuf));	/* expect small files */

	process_data(expectation, fbuf, rd);

	return 1;
}

int
main() {
	DIR *dir;
	struct dirent *dent;
	int processed_files = 0;
	char *str;

	dir = opendir("../data-62");
	assert(dir);

	str = getenv("DATA_62_FILE");
	if(str && strncmp(str, "data-62-", 8) == 0)
		process(str);

	while((dent = readdir(dir))) {
		if(strncmp(dent->d_name, "data-62-", 8) == 0)
			if(process(dent->d_name))
				processed_files++;
	}

	assert(processed_files);
	closedir(dir);

	return 0;
}

