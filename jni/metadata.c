
#include <stdio.h>
#include "logjam.h"
#include <libavformat/avformat.h>
#include <libavutil/dict.h>

int metadata_main(int argc, char **argv)
{
	AVFormatContext *fmt_ctx = NULL;
	AVDictionaryEntry *tag = NULL;
	// AVStream *in_stream;
	int ret;
	int i = 0;
	if (argc != 2) {
		printf("usage: %s <input_file>\n"
				"example program to demonstrate the use of the libavformat metadata API.\n"
				"\n", argv[0]);
		return 1;
	}

	av_register_all();
	if ((ret = avformat_open_input(&fmt_ctx, argv[1], NULL, NULL)))
		return ret;

	while ((tag = av_dict_get(fmt_ctx->metadata, "", tag, AV_DICT_IGNORE_SUFFIX))){
		LOGI("%s=%s\n", tag->key, tag->value);
		printf("%s=%s\n", tag->key, tag->value);
	}

	for (i = 0; i < fmt_ctx->nb_streams; i++) {
		while ((tag = av_dict_get(fmt_ctx->streams[i]->metadata, "", tag, AV_DICT_IGNORE_SUFFIX))){
			LOGI("%s=%s\n", tag->key, tag->value);
			printf("%s=%s\n", tag->key, tag->value);
		}
	}

	avformat_close_input(&fmt_ctx);
	return 0;
}

const char * get_meta_key(int argc, char **argv){
	AVFormatContext *fmt_ctx = NULL;
	AVDictionaryEntry *tag = NULL;
	int ret;
	int i = 0;
	if (argc != 4) {
		printf("usage: %s <input_file>\n"
				"example program to demonstrate the use of the libavformat metadata API.\n"
				"\n", argv[0]);
		return NULL;
	}

	const char* key = argv[3];
	av_register_all();
	if ((ret = avformat_open_input(&fmt_ctx, argv[1], NULL, NULL)))
		return NULL;

	if(strcmp(argv[2],"g") == 0){
		tag = av_dict_get(fmt_ctx->metadata, key, tag, AV_DICT_IGNORE_SUFFIX);
		if(tag && tag->value){
			return tag->value;
		}
		while ((tag = av_dict_get(fmt_ctx->streams[i]->metadata, "", tag, AV_DICT_IGNORE_SUFFIX))){
			if(strcmp(tag->key,key) == 0){
				return tag->value;
			}
		}
	} else if(strcmp(argv[2],"v") == 0){
		for (i = 0; i < fmt_ctx->nb_streams; i++) {
			if(fmt_ctx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
			{
				tag = av_dict_get(fmt_ctx->metadata, key, tag, AV_DICT_IGNORE_SUFFIX);
				if(tag && tag->value){
					return tag->value;
				}
				while ((tag = av_dict_get(fmt_ctx->streams[i]->metadata, "", tag, AV_DICT_IGNORE_SUFFIX))){
					if(strcmp(tag->key,key) == 0){
						return tag->value;
					}
				}
			}
		}
	} else if(strcmp(argv[2],"a") == 0){
		for (i = 0; i < fmt_ctx->nb_streams; i++) {
			if(fmt_ctx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
			{
				tag = av_dict_get(fmt_ctx->metadata, key, tag, AV_DICT_IGNORE_SUFFIX);
				if(tag && tag->value){
					return tag->value;
				}
				while ((tag = av_dict_get(fmt_ctx->streams[i]->metadata, "", tag, AV_DICT_IGNORE_SUFFIX))){
					if(strcmp(tag->key,key) == 0){
						return tag->value;
					}
				}
			}
		}
	}
	return NULL;
}
