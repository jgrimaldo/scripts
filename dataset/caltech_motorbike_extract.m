function caltech_motorbike_extract(image_path, annots, resize_to, save_folder)

    if ~exist('save_folder', 'var') == 1
        mkdir('temp');
        save_folder = 'temp';
        disp('Save folder not specified, saving at temp');
    end

    for i=1:size(annots, 2)
      col = squeeze(annots(:, i));

      xmin = min(col([1 3 5 7]));
      xmax = max(col([1 3 5 7]));
      ymin = min(col([2 4 6 8]));
      ymax = max(col([2 4 6 8]));

      bb = [xmin ymin (xmax - xmin) (ymax - ymin)];
      
      path = [image_path '/' sprintf('%04d', i) '.jpg'];
      cropped_im = imcrop(imread(path), bb);
      
      sprintf('Original %f\n', col)
      sprintf('%i %f %f %f %f', i, bb)
      
      if exist('resize_to', 'var') == 1
          [cropped_im] = imresize(cropped_im, resize_to);
      end           
      
      imwrite(cropped_im, [save_folder '/' sprintf('%04d', i) '.png']); 
    end
end