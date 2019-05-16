python nxt.py 
ffmpeg -y -framerate 30 -i img%03d.png -pix_fmt yuvj420p out.mpeg
rm img*
