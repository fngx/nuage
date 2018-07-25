#include <stdlib.h>
#include <vips/vips.h>

int resizer_init(const int ncpu, const int cache_max, const int cache_mem){
  if(VIPS_INIT("nuage")){
    return 1;
  }
  vips_concurrency_set(ncpu);
  vips_cache_set_max(cache_max);
  vips_cache_set_max_mem(cache_mem);
  return 0;
}

int resizer_process(const char *filename, void **buf, size_t *len, int size, int crop, int quality, int exif){
  VipsImage *img;
  int err;

  size = size > 4000 || size < 0 ? 1000 : size;
  crop = crop == 0 ? VIPS_INTERESTING_NONE : VIPS_INTERESTING_CENTRE;
  quality = quality > 100 || quality < 0 ? 80 : quality;
  exif = exif == 0 ? TRUE : FALSE;

  err = vips_thumbnail(filename, &img, size,
         "size", VIPS_SIZE_DOWN,
         "auto_rotate", TRUE,
         "crop", crop,
          NULL
  );
  if(err != 0){
    return err;
  }

  err = vips_jpegsave_buffer(img, buf, len, "Q", quality, "strip", exif, NULL);
  g_object_unref(img);
  return err;
}
