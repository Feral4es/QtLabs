#connect libraries

library ("IMTest")
library ("car")
library ("GGally")
library ("psych")

data = mtcars

data
summary(data)
ggpairs(data)

#normalize the data:


data$mpg = data$mpg - mean(data$mpg)
data$ mpg = data$ mpg /sqrt(var(data$mpg)) 

data$disp = data$disp - mean(data$disp)
data$disp = data$disp /sqrt(var(data$disp)) 

data$hp = data$hp - mean(data$hp)
data$hp = data$hp /sqrt(var(data$hp)) 

data$drat= data$drat - mean(data$drat)
data$drat = data$drat /sqrt(var(data$drat)) 



#construct a linear regression in pairs between the parameters to determine the linear independence

model1 = lm(disp ~ drat + hp, data)
model1
summary(model1)
model2 = lm(drat ~ disp + hp, data)
model2
summary(model2)
model3 = lm(hp ~ disp + drat, data)
model3
summary(model3)


#build a simple linear model of the dependence of mpg on all describing variables

model4 = lm(mpg ~ disp + hp + drat, data)
model4
summary(model4)

model5 = lm(mpg ~ disp + drat +I(disp * drat), data)
summary(model5)

model6 = lm(mpg ~ drat + hp +I(hp* disp),data)
summary(model6)

model7 = lm(mpg ~ disp + drat +I(drat ^2), data)
summary(model7)

model8 = lm(mpg ~ disp + drat + hp +I(disp ^2), data)
summary(model8)

model9 = lm(mpg ~ disp + drat + hp +I(hp^2), data)
summary(model9)

model10=lm(mpg~ disp + drat + hp +I(hp* drat), data)
summary(model10)

model11 = lm(mpg ~ disp + drat + hp +I(hp* disp), data)
summary(model11)

model12 = lm(mpg ~ disp + hp +I(disp * hp), data)
summary(model12)
vif(model12)


model13 = lm(mpg ~ disp + drat + hp +I(disp * drat), data)
summary(model13)

model14 = lm(mpg ~ disp + hp +log(disp), data)
summary(model14)

model15 = lm(mpg ~ disp + drat +log(disp), data)
summary(model15)

model16 = lm(mpg ~ disp + hp +log(hp), data)
summary(model16)

model17 = lm(mpg ~ disp + drat +log(drat), data)
summary(model17)

model18 = lm(mpg ~ hp + drat +log(hp), data)
summary(model18)

model19 = lm(mpg ~ hp + drat +log(drat), data)
summary(model19)

# the model12 best describes the mpg variable
