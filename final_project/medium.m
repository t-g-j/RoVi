%% tool pos and joint limit
pos = 'SamplePluginPA10/test_folder/rob_medium/t1/jointPosAndToolPos.txt';
pos3 = 'SamplePluginPA10/test_folder/rob_medium/t1/jointPosAndToolPos3p.txt';
delimiterIn = ',';
headerlinesIn = 0;

P = importdata(pos,delimiterIn,headerlinesIn)
P3 = importdata(pos3,delimiterIn,headerlinesIn)


%% const
Jlimit = P(:,1:7)
Jpos = P(:,8:10)
[n m ]= size(P);
frames = [1:n];
Jlimit3 = P3(:,1:7)
%% tool pos

figure
hold on
title('Robot tool position for medium with dt=1s for 1 point');
plot(frames,Jpos(:,1),'*red')
plot(frames,Jpos(:,3),'*blue')
xlabel('Frames');
ylabel('Robot tool position');
legend('x position' ,'y position')

%% Q joint position 1 point
figure
hold on
title('Robot joint variables for medium with dt=1s for 1 point');
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
title('Robot joint variables for medium with dt=1s for 3 point');
plot(frames,Jlimit3(:,1),'y')
plot(frames,Jlimit3(:,2),'r')
plot(frames,Jlimit3(:,3),'m')
plot(frames,Jlimit3(:,4),'c')
plot(frames,Jlimit3(:,5),'g')
plot(frames,Jlimit3(:,6),'b')
plot(frames,Jlimit3(:,7),'k')
xlabel('Frames');
ylabel('Robot joint position');
legend('Q[1)','Q[2)','Q[3)','Q[4)','Q[5)','Q[6)','Q[7)')

