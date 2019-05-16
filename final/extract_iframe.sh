ffmpeg  -i $1 -vf select="eq(pict_type\,PICT_TYPE_I)" -vsync 0 -pix_fmt yuvj420p frame%03d_Dehaze.png
