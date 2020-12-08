---
title: "R Notebook"
output: html_notebook
---


Sys.setlocale(locale = "English")

library("lmtest")
library("rlms")
library("dplyr")
library("GGally")
library(car)
library(sandwich)


#choose regressors:
#oj10 - salary
#oh5 - sex
#o_marst - marital status
#o_diplom - higher education
#o_age - age
#status - type of settlement
#oj6.2 - working week duration


data <- rlms_read("C:/Users/annby/Downloads/r22i_os26c.sav")


data_sorted = select(data, rj10, rh5, status, r_age, r_marst, rj6.2, r_diplom) 



data_sorted = na.omit(data_sorted)
glimpse(data_sorted) 


#normalize salary

salary1 = as.character(data_sorted$rj10)
salary2 = lapply(salary1, as.integer)
salary = as.numeric(unlist(salary2))
data_sorted["salary"] = (salary - mean(salary))/sqrt(var(salary)) 


#normalize age

age1 = as.character(data_sorted$r_age)
age2 = lapply(age1, as.integer)
age3 = as.numeric(unlist(age2))
log_age1 = log(age3)
data_sorted["age"]= (age3 - mean(age3)) / sqrt(var(age3))
data_sorted["log_age"] = (log_age1 - mean(log_age1)/sqrt(var(log_age1)))
data_sorted["age"]
data_sorted["log_age"]


#normalize sex

data_sorted["sex"]=data_sorted$rh5
data_sorted["sex"] = lapply(data_sorted["sex"], as.character)
data_sorted$sex[which(data_sorted$sex!='1')] <- 0
data_sorted$sex[which(data_sorted$sex=='1')] <- 1
data_sorted$sex = as.numeric(data_sorted$sex)


#normalize higher education
#1 - with higher education (h_educ=21,22,23)
#0 - all other

data_sorted["h_educ"] = data_sorted$r_diplom
data_sorted["h_educ"] = lapply(data_sorted["h_educ"], as.character)
data_sorted["higher_educ"] = data_sorted$r_diplom
data_sorted["higher_educ"] = 0
data_sorted$higher_educ[which(data_sorted$h_educ=='21')] <- 1
data_sorted$higher_educ[which(data_sorted$h_educ=='22')] <- 1
data_sorted$higher_educ[which(data_sorted$h_educ=='23')] <- 1


#normalize type of settlement
#1 - large (status=1; status=2)
#0 - all other

data_sorted["status1"]=data_sorted$status
data_sorted["status1"] = lapply(data_sorted["status1"], as.character)
data_sorted["status2"] = 0
data_sorted$status2[which(data_sorted$status1=='1')] <- 1
data_sorted$status2[which(data_sorted$status1=='2')] <- 1
data_sorted$status2 = as.numeric(data_sorted$status2)


#normalize working week duration

dur1 = as.character(data_sorted$rj6.2)
dur2 = lapply(dur1, as.integer)
dur3 = as.numeric(unlist(dur2)) 
data_sorted["log_dur"] = (log(dur3) - mean(log(dur3)))/sqrt(var(log(dur3)))
data_sorted["dur"] = (dur3 - mean(dur3)) / sqrt(var(dur3)) 


#normalize marital status

#wed1 - never married
#wed2 - married
#wed3 - widower/widow

data_sorted["wed"]= data_sorted$r_marst
data_sorted["wed"] = lapply(data_sorted["wed"], as.character)
data_sorted$wed1 = 0
data_sorted$wed1[which(data_sorted$wed=='1')] <- 1
data_sorted$wed1[which(data_sorted$wed=='3')] <- 1
data_sorted$wed1 = as.numeric(data_sorted$wed1) 

data_sorted["wed2"] = lapply(data_sorted["wed"], as.character)
data_sorted$wed2 = 0
data_sorted$wed2[which(data_sorted$wed=='2')] <- 1
data_sorted$wed2 = as.numeric(data_sorted$wed2)

data_sorted["wed3"]=data_sorted$r_marst
data_sorted$wed3 = 0
data_sorted$wed3[which(data_sorted$wed=='4')] <- 1
data_sorted$wed3 = as.numeric(data_sorted$wed3)

data_sorted["wed4"]=data_sorted$r_marst
data_sorted$wed4 = 0
data_sorted$wed4[which(data_sorted$wed=='5')] <- 1
data_sorted$wed4 = as.numeric(data_sorted$wed4)


#form the final dataset, remove from it all respondents with incomplete data

data3 = select(data_sorted, salary, age, sex, higher_educ, status2, dur, wed1,wed2,wed3,wed4, log_age, log_dur)
data3 = na.omit(data3)
data3 
ggpairs(data3)

#construct a simple regression and see if there are linear relationships between the regressors

model1 = lm(data = data3, salary~age + sex + higher_educ + status2 + dur + wed1 + wed2 + wed3 + wed4)
summary(model1)
vif(model1)
#Multiple R-squared:  0.09028,   Adjusted R-squared:  0.08913 

model2 = lm(data = data3, salary ~ age + sex + higher_educ + status2 + dur + log_dur)
summary(model2)
#Multiple R-squared:  0.08732,   Adjusted R-squared:  0.0866 


model3 = lm(data = data3, salary ~ age + sex + higher_educ + status2 + dur + log_age)
summary(model3) 
#Multiple R-squared:  0.1039,    Adjusted R-squared:  0.1032  

model4 = lm(data = data3,  salary ~ age + sex + higher_educ + status2 + dur + I(dur^0.1) + log_age)
summary(model4)
#Multiple R-squared:  0.1055,    Adjusted R-squared:  0.103 

model5 = lm(data = data3, salary ~ age + sex + higher_educ + status2 + dur + I(dur^0.7) + log_age)
summary(model5)
vif(model5)
#Multiple R-squared:  0.1069,    Adjusted R-squared:  0.1045 
#the best model

model6 = lm(data = data3, salary ~ age + sex + higher_educ + status2 + dur + I(dur^1.2))
summary(model6)
#Multiple R-squared:  0.08589,   Adjusted R-squared:  0.0838 


model7 = lm(data = data3, salary ~ age + sex + higher_educ + status2 + dur + I(age^2) + wed1 + wed2 + wed3)
summary(model7)
#Multiple R-squared:  0.1017,    Adjusted R-squared:  0.1006 


model_final = lm(data = data3, salary ~ age + sex + higher_educ + status2 + log_dur + dur + log_age)
summary(model_final)
model5$terms
#model is inaccurate


#individual tasks

#task1

model_final_task1 = lm(data = data3, salary ~ age + sex + higher_educ + status2 + log_dur + dur + log_age, sex == 0 & wed1 == 0)
summary(model_final_task1)


#task2

model_final_task2 = lm(data = data3, salary ~ age + sex + higher_educ + status2 + log_dur + dur + log_age, sex == 0 & status2 == 1 & wed2 == 1)
summary(model_final_task2)
