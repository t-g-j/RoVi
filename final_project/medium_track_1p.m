%% track error import 1 p

errf1 = importdata('SamplePluginPA10/test_folder/rob_medium/t1/errorLog.txt');
errf95= importdata('SamplePluginPA10/test_folder/rob_medium/t95/errorLog.txt');
errf90= importdata('SamplePluginPA10/test_folder/rob_medium/t90/errorLog.txt');
errf85= importdata('SamplePluginPA10/test_folder/rob_medium/t85/errorLog.txt');
errf80= importdata('SamplePluginPA10/test_folder/rob_medium/t80/errorLog.txt');
errf75= importdata('SamplePluginPA10/test_folder/rob_medium/t75/errorLog.txt');
errf70= importdata('SamplePluginPA10/test_folder/rob_medium/t70/errorLog.txt');
errf65= importdata('SamplePluginPA10/test_folder/rob_medium/t65/errorLog.txt');
errf60= importdata('SamplePluginPA10/test_folder/rob_medium/t60/errorLog.txt');
errf55= importdata('SamplePluginPA10/test_folder/rob_medium/t55/errorLog.txt');
errf50= importdata('SamplePluginPA10/test_folder/rob_medium/t50/errorLog.txt');
errf45= importdata('SamplePluginPA10/test_folder/rob_medium/t45/errorLog.txt');
errf40= importdata('SamplePluginPA10/test_folder/rob_medium/t40/errorLog.txt');
errf35= importdata('SamplePluginPA10/test_folder/rob_medium/t35/errorLog.txt');
errf30= importdata('SamplePluginPA10/test_folder/rob_medium/t30/errorLog.txt');
errf25= importdata('SamplePluginPA10/test_folder/rob_medium/t25/errorLog.txt');
errf20= importdata('SamplePluginPA10/test_folder/rob_medium/t20/errorLog.txt');
errf15= importdata('SamplePluginPA10/test_folder/rob_medium/t15/errorLog.txt');
errf10= importdata('SamplePluginPA10/test_folder/rob_medium/t10/errorLog.txt');
errf05= importdata('SamplePluginPA10/test_folder/rob_medium/t5/errorLog.txt');
errVec =[errf1,errf95,errf90,errf85,errf80,errf75,errf70,errf65,errf60,errf55,errf50,errf45,errf40,errf35,errf30,errf25,errf20,errf15,errf10,errf05]

timeVec =[1 , .95,.9,.85,.8,.75,.7,.65,.6,.55,.5,.45,.40,.35,.3,.25,.2,.15,.1,.05]

plot(timeVec,errVec)
title('Tracking error in Euclidean distance in pixel for different dt')
xlabel('dt')
ylabel('maximum error in pixels')
legend('slow 1p','slow 3p','medium 1p','medium 3p','fast 1p','fast 3p')