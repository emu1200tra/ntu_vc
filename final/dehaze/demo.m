function demo(index)
    warning('off','all');

    for i =1:index
        tic;
	name=sprintf('frame%03d.png',i);
	
        image = double(imread(name))/255;

        image = imresize(image, 1);

        %result = dehaze(image, 0.95, 30);
        result = dehaze(image, 0.95, 30);
        toc;

        %figure, imshow(image)
        %figure, imshow(result)
	name=sprintf('frame%03d_Dehaze.png',i);
        imwrite(result , name);
    end
    warning('on','all');
end
