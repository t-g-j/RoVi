file = 'SamplePluginPA10/test_folder/rob_slow/t1/JointPosAndToolPos.txt';
delimiterIn = ',';
headerlinesIn = 0;
P = importdata(file,delimiterIn,headerlinesIn)


Jlimit = P(:,1:7)
Jpos = P(:,8:10)
[n m ]= size(P);
frames = [1:n];

figure
hold on
title('Robot tool position for slow with dt=1s for 1 point');
plot(frames,Jpos(:,1),'*red')
plot(frames,Jpos(:,3),'*blue')
xlabel('Frames');
ylabel('Robot position');

figure
hold on
title('Robot joint variables for slow with dt=1s for 1 point');
plot(frames,Jlimit(:,1),'y')
plot(frames,Jlimit(:,1),'y')
plot(frames,Jlimit(:,1),'y')
plot(frames,Jlimit(:,1),'y')
plot(frames,Jlimit(:,1),'y')
plot(frames,Jlimit(:,1),'y')