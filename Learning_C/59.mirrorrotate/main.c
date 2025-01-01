#include <assert.h>
#include <libexif/exif-content.h>
#include <libexif/exif-data.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    ExifData* e_data = exif_data_new_from_file("IMG_20241214_122143.jpg");
    if (e_data) {
        char value[128] = { 0 };
        exif_content_get_value((e_data->ifd[0]), EXIF_TAG_ORIENTATION, value, sizeof(value));
        printf("EXIF_TAG_ORIENTATION = %s\n", value);
    } else {
        exit(-1);
    }
    exif_data_unref(e_data);
    return 0;
}