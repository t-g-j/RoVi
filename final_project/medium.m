filename = 'SamplePluginPA10/test_folder/rob_medium/t1/JointLimitAndVelocities.txt';
pos = 'SamplePluginPA10/test_folder/rob_medium/t1/jointPosAndLimit.txt';
pos3 = 'SamplePluginPA10/test_folder/rob_medium/t1/jointPosAndLimit3p.txt';
delimiterIn = ',';
headerlinesIn = 0;
A = importdata(filename,delimiterIn,headerlinesIn)
P = importdata(pos,delimiterIn,headerlinesIn)
P3 = importdata(pos3,delimiterIn,headerlinesIn)

% Joint limit and Jposition for 1 point
Jlimit = P(:,1:7)
Jpos = P(:,8:10)
[n m ]= size(P);
frames = [1:n];
figure
hold on
title('Robot tool position for medium with dt=1s for 1 point');
plot(frames,Jpos(:,1),'*red')
plot(frames,Jpos(:,3),'*blue')
xlabel('Frames');
ylabel('Robot position');

% Joint limit and Jposition for 3 points
Jlimit3 = P3(:,1:7)
Jpos3 = P3(:,8:10)

% figure
% hold on
% title('Robot tool position for medium with dt=1s for 3 point');
% plot(frames,Jpos3(:,1),'*red')
% plot(frames,Jpos3(:,3),'*blue')
% xlabel('Frames');
% ylabel('Robot position');