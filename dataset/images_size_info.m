function [sizes] = images_size_infos(images)
  
 % width and height
 sizes = [0 0];
 
 for i=1:length(images)
     im = imread(images(i).name);
     
     sizes(1) = sizes(1) + size(im, 1);
     sizes(2) = sizes(2) + size(im, 2);
 end
 
 sizes = round(sizes ./ length(images));
end
 