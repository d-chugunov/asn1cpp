/*
 * Mode of operation:
 * Each of the *.in files is XER-decoded, then converted into DER,
 * then decoded from DER and encoded into XER again. The resulting
 * stream is compared with the corresponding .out file.
 */
#undef	NDEBUG
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>	/* for chdir(2) */
#include <string.h>
#include <dirent.h>
#include <ctype.h>	/* for isspace(3) */
#include <assert.h>
#include <errno.h>
#include <iostream>

#ifdef SINGLE_UNIT
#include <asn.hpp>
#else
#include <PDU.hpp>
#endif

using namespace ModuleTestXERDecoding;

enum expectation {
	EXP_OK,		/* Encoding/decoding must succeed */
	EXP_BROKEN,	/* Decoding must fail */
	EXP_DIFFERENT,	/* Reconstruction will yield different encoding */
};


std::vector<uint8_t> buf;

enum der_or_xer {
	AS_DER
};

static void
save_object_as(PDU *st, enum der_or_xer how) {
	asn_enc_rval_t rval; /* Return value */

	/*
	 * Save object using specified method.
	 */
	switch(how) {
	case AS_DER:
    rval = st->EncodeDer(buf);
		break;
	}
	if (rval.encoded == -1) {
		fprintf(stderr,
			"Cannot encode %s: %s\n",
			rval.failed_type->name, strerror(errno));
		assert(rval.encoded != -1);
		return;
	}

	fprintf(stderr, "SAVED OBJECT IN SIZE %d\n", buf.size());
}

static std::unique_ptr<PDU>
load_object_from(enum expectation expectation, unsigned char *fbuf, size_t size, enum der_or_xer how) {
	asn_dec_rval_t rval;
	std::unique_ptr<PDU> st;
	size_t csize = 1;

	if(getenv("INITIAL_CHUNK_SIZE"))
		csize = atoi(getenv("INITIAL_CHUNK_SIZE"));

	/* Perform multiple iterations with multiple chunks sizes */
	for(; csize < 20; csize += 1) {
		int fbuf_offset = 0;
		int fbuf_left = size;
		int fbuf_chunk = csize;

		fprintf(stderr, "LOADING OBJECT OF SIZE %zd, chunks %zd\n",
			size, csize);

		st.reset();

		do {
			fprintf(stderr, "Decoding bytes %d..%d (left %d)\n",
				fbuf_offset,
					fbuf_chunk < fbuf_left
						? fbuf_chunk : fbuf_left,
					fbuf_left);
			if(st) {
				fprintf(stderr, "=== currently ===\n");
				st->Print(std::cerr);
				fprintf(stderr, "=== end ===\n");
			} else {
        st.reset(new PDU);
      }
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
			if(how == AS_DER) {
				assert(fbuf_offset == (ssize_t)size);
			} else {
				assert(fbuf_offset - size < 2
				|| (fbuf_offset + 1 /* "\n" */  == (ssize_t)size
					&& fbuf[size - 1] == '\n')
				|| (fbuf_offset + 2 /* "\r\n" */  == (ssize_t)size
					&& fbuf[size - 2] == '\r'
					&& fbuf[size - 1] == '\n')
				);
			}
		} else {
			assert(rval.code != RC_OK);
			fprintf(stderr, "Failed, but this was expected\n");
      st.reset();
		}
	}

	if(st) st->Print(std::cerr);
	return st;
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

	if(ext == 0 || strcmp(ext, ".in"))
		return 0;

	switch(ext[-1]) {
	case 'B':	/* The file is intentionally broken */
		expectation = EXP_BROKEN; break;
	case 'X':
	case 'D':	/* Reconstructing should yield different data */
		expectation = EXP_DIFFERENT; break;
	case 'E':
	default:
		expectation = EXP_OK; break;
	}

	fprintf(stderr, "\nProcessing file [../%s]\n", fname);

	std::string filepath = "../data-70/" + std::string(fname);
	//ret = chdir("../data-70");
	//assert(ret == 0);
	fp = fopen(filepath.c_str(), "r");
	//ret = chdir("../test-check-70");
	//assert(ret == 0);
	assert(fp);

	rd = fread(fbuf, 1, sizeof(fbuf), fp);
	fclose(fp);

	assert(rd > 0 && (size_t)rd < sizeof(fbuf));	/* expect small files */

	return 1;
}

int
main() {
	DIR *dir;
	struct dirent *dent;
	int processed_files = 0;
	char *str;

	/* Process a specific test file */
	str = getenv("DATA_70_FILE");
	if(str && strncmp(str, "data-70-", 8) == 0)
		process(str);

	dir = opendir("../data-70");
	assert(dir);

	/*
	 * Process each file in that directory.
	 */
	while((dent = readdir(dir))) {
		if(strncmp(dent->d_name, "data-70-", 8) == 0)
			if(process(dent->d_name))
				processed_files++;
	}

	assert(processed_files);
	closedir(dir);

	return 0;
}

