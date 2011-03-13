function caltech_motorbike_extract(image_path, annots, resize_to, save_folder)

    if ~exist('save_folder', 'var') == 1
        mkdir('temp');
        save_folder = 'temp';
        disp('Save folder not specified, saving at temp');
    end

    for i=1:size(annots, 2)
      col = squeeze(annots(:, i));

      xtl = col(3);
      ytl = col(4);
      xbr = col(7);
      ybr = col(8);

      bb = [xtl ytl (xbr - xtl) (ybr - ytl)];
      
      path = [image_path '/' sprintf('%04d', i) '.jpg'];
      cropped_im = imcrop(imread(path), bb);
      
      if exist('resize_to', 'var') == 1
          [cropped_im map] = imresize(cropped_im, resize_to);
      end           
      
      imwrite(cropped_im, [save_folder '/' sprintf('%04d', i) '.png']); 
    end
end