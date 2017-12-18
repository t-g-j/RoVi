close all
clc
clear
file = 'SamplePluginPA10/test_folder/rob_slow/visionError.txt';
delimiterIn = ',';
erVi = importdata(file,delimiterIn)

res1 = sqrt(erVi(:,1).^2 + erVi(:,2).^2);
figure
plot(res1(2:500) )
title('Tracking error')
ylabel('Euclidean distance px')
xlabel('Frames')
%%
file ='SamplePluginPA10/test_folder/rob_slow/markerError.txt';
delimiterIn = ',';
erMa = importdata(file,delimiterIn);

res2= sqrt(erMa(:,1).^2 +erMa(:,2).^2);
figure
plot(res2(2:500))
title('Tracking error')
ylabel('Euclidean distance px')
xlabel('Frames')
%%
file ='SamplePluginPA10/test_folder/rob_medium/visionError.txt';
delimiterIn = ',';
erVi2 = importdata(file,delimiterIn);

res3 = sqrt(erVi2(:,1).^2+erVi2(:,2).^2);
figure
plot(res3(2:166))
title('Tracking error')
ylabel('Euclidean distance px')
xlabel('Frames')
%%
file = 'SamplePluginPA10/test_folder/rob_medium/markerError.txt';
delimiterIn = ',';
erMa2 = importdata(file,delimiterIn);

res4= sqrt(erMa2(:,1).^2+erMa2(:,2).^2);
figure
plot(res4(2:166))
title('Tracking error')
ylabel('Euclidean distance px')
xlabel('Frames')
%%
file ='SamplePluginPA10/test_folder/rob_fast/visionError.txt';
delimiterIn = ',';
erVi3 = importdata(file,delimiterIn);

res5 = sqrt(erVi3(:,1).^2+erVi3(:,2).^2)
figure
plot(res5(2:49))
title('Tracking error')
ylabel('Euclidean distance px')
xlabel('Frames')
%%
file ='SamplePluginPA10/test_folder/rob_fast/markerError.txt'
delimiterIn = ',';
erMa3 = importdata(file,delimiterIn);

res6= sqrt(erMa3(:,1).^2+erMa3(:,2).^2)
figure
plot(res6(3:49))
title('Tracking error')
ylabel('Euclidean distance px')
xlabel('Frames')