//
// Created by Sandy H on 01/06/24.
//
#include <curl/curl.h>

#ifndef REST_API_URL_DEBUG_H
#define REST_API_URL_DEBUG_H

#endif //REST_API_URL_DEBUG_H

/**
 *
 * sandy.haryono@thalesgroup.com
 *
 */

struct data {
    char trace_ascii; /* 1 or 0 */
};
struct data config;


static void dump(const char *text, FILE *stream, unsigned char *ptr, size_t size,char nohex)
{
    size_t i;
    size_t c;

    unsigned int width = 0x10;

    if(nohex)
        /* without the hex output, we can fit more on screen */
        width = 0x40;

    fprintf(stream, "%s, %10.10lu bytes (0x%8.8lx)\n",
            text, (unsigned long)size, (unsigned long)size);

    for(i = 0; i<size; i += width) {

        fprintf(stream, "%4.4lx: ", (unsigned long)i);

        if(!nohex) {
            /* hex not disabled, show it */
            for(c = 0; c < width; c++)
                if(i + c < size)
                    fprintf(stream, "%02x ", ptr[i + c]);
                else
                    fputs("   ", stream);
        }

        for(c = 0; (c < width) && (i + c < size); c++) {
            /* check for 0D0A; if found, skip past and start a new line of output */
            if(nohex && (i + c + 1 < size) && ptr[i + c] == 0x0D &&
               ptr[i + c + 1] == 0x0A) {
                i += (c + 2 - width);
                break;
            }
            fprintf(stream, "%c",
                    (ptr[i + c] >= 0x20) && (ptr[i + c]<0x80)?ptr[i + c]:'.');
            /* check again for 0D0A, to avoid an extra \n if it's at width */
            if(nohex && (i + c + 2 < size) && ptr[i + c + 1] == 0x0D &&
               ptr[i + c + 2] == 0x0A) {
                i += (c + 3 - width);
                break;
            }
        }
        fputc('\n', stream); /* newline */
    }
    fflush(stream);
}


static int my_trace(CURL *handle, curl_infotype type, char *data, size_t size, void *userp)
{
    struct data *config = (struct data *)userp;
    const char *text;
    (void)handle; /* prevent compiler warning */

    switch(type) {
        case CURLINFO_TEXT:
            fprintf(stderr, "== Info: %s", data);
            return 0;
        case CURLINFO_HEADER_OUT:
            text = "=> Send header";
            break;
        case CURLINFO_DATA_OUT:
            text = "=> Send data";
            break;
        case CURLINFO_SSL_DATA_OUT:
            text = "=> Send SSL data";
            break;
        case CURLINFO_HEADER_IN:
            text = "<= Recv header";
            break;
        case CURLINFO_DATA_IN:
            text = "<= Recv data";
            break;
        case CURLINFO_SSL_DATA_IN:
            text = "<= Recv SSL data";
            break;
        default: /* in case a new one is introduced to shock us */
            return 0;
    }

    dump(text, stderr, (unsigned char *)data, size, config->trace_ascii);
    return 0;
}
