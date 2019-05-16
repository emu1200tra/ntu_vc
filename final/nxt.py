from PIL import Image
from string import atoi
f=open('out.txt')
im2 = Image.open('frame001_Dehaze.jpg') # Can be many different formats.
im = Image.new(im.mode,im.size);
data=f.readline()
data=f.readline()
pix = im.load()
pix2=im2.load()
framenum=1
keynum=2
while data!='':
    mv=data.split(',')
    targ=atoi(mv[0])
    if(targ!=framenum):
        framename="frame%03d.jpg" % framenum
        framenum=framenum+1
        im2.save(framename)
        im=im2.copy()
        pix = im.load()
        pix2=im2.load()
        
        if(targ!=framenum):
            framename="frame%03d.jpg" % framenum
            keyname="frame%03d_Dehaze.jpg" % keynum
            framenum=framenum+1
            im2=Image.open(keyname)
            keynum=keynum+1
            
            im2.save(framename)
            im=im2.copy()
            pix = im.load()
            pix2=im2.load()
    blockw=atoi(mv[2])
    blockh=atoi(mv[3])
    srcx=atoi(mv[4])
    srcy=atoi(mv[5])
    dstx=atoi(mv[6])
    dsty=atoi(mv[7])
    for i in range(0,blockw):
        for j in range(0,blockh):
            pix2[dstx-8+i,dsty-8+j]=pix[srcx-8+i,atoi(srcy-8+j]
    data=f.readline()


framename="frame%03d.jpg" % framenum
im2.save(framename)  
