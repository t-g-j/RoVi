file = 'SamplePluginPA10/test_folder/rob_slow/t1/JointPosAndToolPos.txt';
file2 = 'SamplePluginPA10/test_folder/rob_slow/t1/JointPosAndToolPos3p.txt';
delimiterIn = ',';
headerlinesIn = 0;
P = importdata(file,delimiterIn,headerlinesIn)
P3= importdata(file2,delimiterIn,headerlinesIn)
%% track error import

errf1 = importdata('SamplePluginPA10/test_folder/rob_slow/t1/errorLog.txt');
errf95= importdata('SamplePluginPA10/test_folder/rob_slow/t95/errorLog.txt');
errf90= importdata('SamplePluginPA10/test_folder/rob_slow/t90/errorLog.txt');
errf85= importdata('SamplePluginPA10/test_folder/rob_slow/t85/errorLog.txt');
errf80= importdata('SamplePluginPA10/test_folder/rob_slow/t80/errorLog.txt');
errf75= importdata('SamplePluginPA10/test_folder/rob_slow/t75/errorLog.txt');
errf70= importdata('SamplePluginPA10/test_folder/rob_slow/t70/errorLog.txt');
errf65= importdata('SamplePluginPA10/test_folder/rob_slow/t65/errorLog.txt');
errf60= importdata('SamplePluginPA10/test_folder/rob_slow/t60/errorLog.txt');
errf55= importdata('SamplePluginPA10/test_folder/rob_slow/t55/errorLog.txt');
errf50= importdata('SamplePluginPA10/test_folder/rob_slow/t50/errorLog.txt');
errf45= importdata('SamplePluginPA10/test_folder/rob_slow/t45/errorLog.txt');
errf40= importdata('SamplePluginPA10/test_folder/rob_slow/t40/errorLog.txt');
errf35= importdata('SamplePluginPA10/test_folder/rob_slow/t35/errorLog.txt');
errf30= importdata('SamplePluginPA10/test_folder/rob_slow/t30/errorLog.txt');
errf25= importdata('SamplePluginPA10/test_folder/rob_slow/t25/errorLog.txt');
errf20= importdata('SamplePluginPA10/test_folder/rob_slow/t20/errorLog.txt');
errf15= importdata('SamplePluginPA10/test_folder/rob_slow/t15/errorLog.txt');
errf10= importdata('SamplePluginPA10/test_folder/rob_slow/t10/errorLog.txt');
errf05= importdata('SamplePluginPA10/test_folder/rob_slow/t5/errorLog.txt');

%% const
Jlimit = P(:,1:7)
Jpos = P(:,8:10)
[n m ]= size(P);
frames = [1:n];
Jlimit3 = P3(:,1:7)


%% Tool pos

figure
hold on
title('Robot tool position for slow with dt=1s for 1 point');
plot(frames,Jpos(:,1),'*red')
plot(frames,Jpos(:,3),'*blue')
xlabel('Frames');
ylabel('Robot tool position');
legend('x position' ,'y position')

%% Q joint position 1 point
figure
hold on
title('Robot joint variables for slow with dt=1s for 1 point');
plot(frames,Jlimit(:,1),'y')
plot(frames,Jlimit(:,2),'r')
plot(frames,Jlimit(:,3),'m')
plot(frames,Jlimit(:,4),'c')
plot(frames,Jlimit(:,5),'g')
plot(frames,Jlimit(:,6),'b')
plot(frames,Jlimit(:,7),'k')
legend('Q[1)','Q[2)','Q[3)','Q[4)','Q[5)','Q[6)','Q[7)')
%% Q joints position 3 point
figure
hold on
title('Robot joint variables for slow with dt=1s for 3 point');
plot(frames,Jlimit3(:,1),'y')
plot(frames,Jlimit3(:,2),'r')
plot(frames,Jlimit3(:,3),'m')
plot(frames,Jlimit3(:,4),'c')
plot(frames,Jlimit3(:,5),'g')
plot(frames,Jlimit3(:,6),'b')
plot(frames,Jlimit3(:,7),'k')
xlabel('Frames');
ylabel('Robot joint position');
legend('Q[1)','Q[2)','Q[3)','Q[4)','Q[5)','Q[6)','Q[7]')
%% error plotting
% figure
% hold on
% title('Maximum error in pixel against the different dt')
