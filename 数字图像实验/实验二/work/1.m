%close all;clear;
f1=zeros(256,256);
f2=zeros(256,256);
for m=64:1:192
    for n=112:1:144
        f1(m,n)=100/255;
        f2(m,n)=(-1)^(m+n)*100/255;
    end
end

f3=imrotate(f2,-90,'nearest');
f4=imrotate(f1,-90,'nearest');
f5=f1+f4;
f6=f2+f3;

fft_f1=log(1+abs(fft2(f1)));
fft_f2=log(1+abs(fft2(f2)));
fft_f3=log(1+abs(fft2(f3)));
fft_f5=log(1+abs(fft2(f5)));
fft_f6=log(1+abs(fft2(f6)));

figure
subplot(1,2,1);?
imshow(f1);
title('f1的图像');
subplot(1,2,2);?
imshow(fft_f1,[]);
title('FFT(f1)?的幅度频谱');

figure
subplot(1,2,1);?
imshow(f2);
title('f2的图像');
subplot(1,2,2);?
imshow(fft_f2,[]);
title('FFT(f2)?的幅度频谱');

figure
subplot(1,2,1);?
imshow(fft_f2,[]);
title('FFT(f2)?的幅度频谱');
subplot(1,2,2);?
imshow(fft_f3,[]);
title('FFT(f3)?的幅度频谱');

figure
imshow(fft_f5,[]);
title('FFT(f5)?的幅度频谱');

figure
imshow(fft_f6,[]);
title('FFT(f6)?的幅度频谱');