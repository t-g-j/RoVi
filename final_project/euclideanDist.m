close all
clc
clear
file = 'SamplePluginPA10/test_folder/rob_slow/visionError.txt';
delimiterIn = ',';
erVi = importdata(file,delimiterIn)
erVi =erVi.^2;
res1 = sqrt(erVi(:,1).*erVi(:,2));
figure
plot(res1(2:500) )
title('Tracking error')
ylabel('Euclidean distance px')
xlabel('Frames')
%%
file ='SamplePluginPA10/test_folder/rob_slow/markerError.txt';
delimiterIn = ',';
erMa = importdata(file,delimiterIn);
erMa =erMa.^2;
res2= sqrt(erMa(:,1).*erMa(:,2));
figure
plot(res2(2:500))
title('Tracking error')
ylabel('Euclidean distance px')
xlabel('Frames')
%%
file ='SamplePluginPA10/test_folder/rob_medium/visionError.txt';
delimiterIn = ',';
erVi2 = importdata(file,delimiterIn);
erVi2 =erVi2.^2;
res3 = sqrt(erVi2(:,1).*erVi2(:,2));
figure
plot(res3(2:166))
title('Tracking error')
ylabel('Euclidean distance px')
xlabel('Frames')
%%
file = 'SamplePluginPA10/test_folder/rob_medium/markerError.txt';
delimiterIn = ',';
erMa2 = importdata(file,delimiterIn);
erMa2 =erMa2.^2;
res4= sqrt(erMa2(:,1).*erMa2(:,2));
figure
plot(res4(2:166))
title('Tracking error')
ylabel('Euclidean distance px')
xlabel('Frames')
%%
file ='SamplePluginPA10/test_folder/rob_fast/visionError.txt';
delimiterIn = ',';
erVi3 = importdata(file,delimiterIn);
erVi3 = erVi3.^2;
res5 = sqrt(erVi3(:,1).*erVi3(:,2))
figure
plot(res5(2:49))
title('Tracking error')
ylabel('Euclidean distance px')
xlabel('Frames')
%%
file ='SamplePluginPA10/test_folder/rob_fast/markerError.txt'
delimiterIn = ',';
erMa3 = importdata(file,delimiterIn);
erMa3 =erMa3.^2
res6= sqrt(erMa3(:,1).*erMa3(:,2))
figure
plot(res6(3:49))
title('Tracking error')
ylabel('Euclidean distance px')
xlabel('Frames')