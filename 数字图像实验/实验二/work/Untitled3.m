f = imread('saturn.tif');
a=f(:,:,1);
b=f(:,:,2);
c=f(:,:,3);
fshow=cat(3,a,b,c);
imshow(fshow);
title('ԭʼͼ��');
F=fft2(f); 
figure;
subplot(221);
imshow(abs(F));%��ʾͼ��Ƶ��
FC=fftshift(F);   %���任ԭ���Ƶ�Ƶ�ʾ��ε�����
figure;
imshow(abs(FC));%��ʾ����ƽ��ͼ��Ƶ��
S2= log(1+ abs(F));
figure;
imshow(S2);%��ʾ��ǿͼ��Ƶ��
for i=1:1:256;
    for j=1:1:256;
        [i,j]=meshgrid(i,j);
    end
end
mesh(abs(F));
title('��άͼ����ʾ������');