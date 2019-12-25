F = imread('t1.jpg');
img = F;
[n, m] = size(F);
for i = 1 : n
    for j = 1 : m
        if(F(i,j)>=0 & F(i,j)<=128)
            F(i,j) = 0;
        else
            F(i,j) = 255;
        end
    end
end
subplot(2,2,1);imshow(img);
subplot(2,2,2);imshow(F);
subplot(2,2,3);imhist(img);
subplot(2,2,4);imhist(F);