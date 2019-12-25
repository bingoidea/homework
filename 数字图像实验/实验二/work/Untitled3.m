f = imread('saturn.tif');
a=f(:,:,1);
b=f(:,:,2);
c=f(:,:,3);
fshow=cat(3,a,b,c);
imshow(fshow);
title('原始图像');
F=fft2(f); 
figure;
subplot(221);
imshow(abs(F));%显示图像频谱
FC=fftshift(F);   %将变换原点移到频率矩形的中心
figure;
imshow(abs(FC));%显示中心平移图像频谱
S2= log(1+ abs(F));
figure;
imshow(S2);%显示增强图像频谱
for i=1:1:256;
    for j=1:1:256;
        [i,j]=meshgrid(i,j);
    end
end
mesh(abs(F));
title('三维图像显示幅度谱');