#!/usr/bin/env python
# coding: utf-8


import pandas as pd
import numpy as np
from fancyimpute import KNN
from scipy.stats import chi2_contingency
import matplotlib.pyplot as plt
import seaborn as sns
import matplotlib.pyplot as plt
from random import randrange,uniform
from sklearn.model_selection import train_test_split
from sklearn import tree
from sklearn.tree import export_graphviz               
from sklearn.metrics import accuracy_score            
from sklearn.metrics import confusion_matrix           
from sklearn.ensemble import RandomForestClassifier    
import statsmodels.api as sn                           
from sklearn.neighbors import KNeighborsClassifier             
from sklearn import model_selection                  
fromsklearn.metrics import classification_report,roc_auc_score,roc_curve 
from sklearn.metrics import classification_report      
import pickle                                        
import statsmodels.api as sm
from statsmodels.stats.outliers_influence import variance_inflation_factor  
from statsmodels.tools.tools import add_constant
np.random.seed(123) 
pd.options.mode.chained_assignment = None  


data = pd.read_csv('hotel_bookings.csv')


data = data [["hotel", "is_canceled","lead_time",
              "arrival_date_year", "arrival_date_month",
              "arrival_date_week_number", "arrival_date_day_of_month",
              "stays_in_weekend_nights", "stays_in_week_nights",
              "adults", "children", "babies", "meal", "country",
              "market_segment", "distribution_channel", "is_repeated_guest",
              "previous_cancellations", "previous_bookings_not_canceled",
              "reserved_room_type", "assigned_room_type", "booking_changes",
              "deposit_type", "agent", "company", "days_in_waiting_list",
              "customer_type", "adr", "required_car_parking_spaces",
              "total_of_special_requests", "reservation_status", "reservation_status_date"]]

#hotel – название отеля
#is_canceled – отмена брони bool
#lead_time – время выполнения заказа
#arrival_date_year – год заселения
#arrival_date_month – месяц заселения
#arrival_date_week_number – номер недели заселения
#arrival_date_day_of_month – день заселения
#stays_in_weekend_nights – ночь в выходные
#stays_in_week_nights – на ночь
#adults – взрослые
#children – дети
#babies – груднички
#meal – еда
#country – страна
#market_segment – сегмент рынка
#distribution_channel – канал перехода
#is_repeated_guest – повторное заселение bool
#previous_cancellations – ранее были отмены bool
#previous_bookings_not_canceled – ранее брони не отменялись bool
#reserved_room_type – тип номера
#assigned_room_type – присвоен номер
#booking_changes – изменения в брони
#deposit_type – тип депозита
#agent – агент
#company – компания
#days_in_waiting_list – дни в списке ожидания
#customer_type – тип клиента
#adr – 
#required_car_parking_spaces – парковочное место
#total_of_special_requests – сумма спец. запросов
#reservation_status – статус брони
#reservation_status_date – дата обновления статуса брони



data.head()


data.describe()


data.info()


type(data)


data.shape


y = data["is_canceled"]
sns.countplot(y)
is_canceled_often = data.is_canceled.value_counts()
print(is_canceled_often)


sns.barplot(data["children"],data["is_canceled"])


#При бронировании с детьми, отмены происходят реже


data.columns = ["hotel", "is_canceled","lead_time",
              "arrival_date_year", "arrival_date_month",
              "arrival_date_week_number", "arrival_date_day_of_month",
              "stays_in_weekend_nights", "stays_in_week_nights",
              "adults", "children", "babies", "meal", "country",
              "market_segment", "distribution_channel", "is_repeated_guest",
              "previous_cancellations", "previous_bookings_not_canceled",
              "reserved_room_type", "assigned_room_type", "booking_changes",
              "deposit_type", "agent", "company", "days_in_waiting_list",
              "customer_type", "adr", "required_car_parking_spaces",
              "total_of_special_requests", "reservation_status", "reservation_status_date"]


data['children'][data['children'] == 0] = 'without_ch'
data['children'][data['children'] > 0] = 'with_ch'


data['babies'][data['babies'] == 0] = 'without_bab'
data['babies'][data['babies'] > 0] = 'with_bab'


data['is_repeated_guest'][data['is_repeated_guest'] == 0] = 'non_repeated_guest'
data['is_repeated_guest'][data['is_repeated_guest'] == 1] = 'repeated_guest'


data['previous_cancellations'][data['previous_cancellations'] == 0] = 'without_cancellations'
data['previous_cancellations'][data['previous_cancellations'] == 1] = 'cancellations'


data['exercise_induced_angina'][data['exercise_induced_angina'] == 0] = 'no'
data['exercise_induced_angina'][data['exercise_induced_angina'] == 1] = 'yes'


data['customer_type'][data['customer_type'] == 'Contract'] = 'Contract'
data['customer_type'][data['customer_type'] == 'Group'] = 'Group'
data['customer_type'][data['customer_type'] == 'Transient'] = 'Transient'
data['customer_type'][data['customer_type'] == 'Transient-Party'] = 'Transient-Party'


data['meal'][data['meal'] == 'BB'] = 'meal_BB'
data['meal'][data['meal'] == 'FB'] = 'meal_FB'
data['meal'][data['meal'] == 'HB'] = 'meal_HB'
data['meal'][data['meal'] == 'SC'] = 'meal_SC'
data['meal'][data['meal'] == 'Undefined'] = 'meal_Undefined'


data['booking_changes'][data['booking_changes'] == 0] = 'no_booking_changes'
data['booking_changes'][10 >= data['booking_changes'] >= 1] = 'booking_changes_before_10'
data['booking_changes'][data['booking_changes'] > 11] = 'booking_changes_more_10'

data['days_in_waiting_list'][100 >= data['days_in_waiting_list'] >= 0] = 'days_in_waiting_list_small'
data['days_in_waiting_list'][data['days_in_waiting_list'] > 100] = 'days_in_waiting_list_long'


#Процент с отменами и без отмен


list = []
for i in range(0,data.shape[1]):
    if(data.iloc[:,i].dtypes == 'object'):
        data.iloc[:,i] = pd.Categorical(data.iloc[:,i])
        data.iloc[:,i] = data.iloc[:,i].cat.codes
        data.iloc[:,i] = data.iloc[:,i].astype('object')
    list.append(data.columns[i])


sns.countplot(x='is_canceled',data=data,palette="bwr")
plt.show()


countWithout_ch = len(data[data.children == 0])
countWith_ch = len(data[data.children > 0])
print("Процент посетителей без детей:{:.2f}%".format((countWithout_ch)/(len(data.children))*100))
print("Процент посетителей с детьми:{:.2f}%".format((countWith_ch)/(len(data.children))*100))


countNoCanceled = len(data[data.is_canceled == 0])
countHaveCanceled = len(data[data.is_canceled == 1])
print("Процент без отмены брони: {:.2f}%%".format((countNoCanceled / (len(data.is_canceled))*100)))
print("Процент отмененных броней: {:.2f}%%".format((countHaveCanceled / (len(data.is_canceled))*100)))


data.groupby('is_canceled').mean()


#Частота отмен брони при изменениях в брони


pd.crosstab(data.booking_changes,data.is_canceled).plot(kind="bar",figsize=(20,6))
plt.title('Частота отмен брони при изменениях в брони')
plt.xlabel('booking changes')
plt.ylabel('Frequency')
plt.show()


#Частота отмен с детьми и без


pd.crosstab(data.children,data.is_canceled).plot(kind="bar",figsize=(15,6),color=['blue','#AA1111' ])
plt.title('Частота отмен с детьми и без')
plt.xlabel('children (0 = without, 1 = with)')
plt.xticks(rotation=0)
plt.legend(["Haven't Canceled", "Have Canceled"])
plt.ylabel('Frequency')
plt.show()

#Частота отмен с младенцами и без


pd.crosstab(data.babies,data.is_canceled).plot(kind="bar",figsize=(15,6),color=['blue','#AA1111' ])
plt.title('Частота отмен с младенцами и без')
plt.xlabel('babies (0 = without, 1 = with)')
plt.xticks(rotation=0)
plt.legend(["Haven't Canceled", "Have Canceled"])
plt.ylabel('Frequency')
plt.show()


#Сегмент рынка и максимальная частота отмен брони


plt.scatter(x=data.market_segment[data.is_canceled==1], y=data.thalassemia[(data.is_canceled==1)], c="green")
plt.scatter(x=data.market_segment[data.is_canceled==0], y=data.thalassemia[(data.is_canceled==0)])
plt.legend(["Canceled", "Not Canceled"])
plt.xlabel("Marketing Segment")
plt.ylabel("Maximum Canceled")
plt.show()

#Канал перехода и максимальная частота отмен брони


plt.scatter(x=data.distribution_channel[data.is_canceled==1], y=data.thalassemia[(data.is_canceled==1)], c="green")
plt.scatter(x=data.distribution_channel[data.is_canceled==0], y=data.thalassemia[(data.is_canceled==0)])
plt.legend(["Canceled", "Not Canceled"])
plt.xlabel("Distribution Channel")
plt.ylabel("Maximum Canceled")
plt.show()


#Test Split


predictors = data.drop("is_canceled",axis=1)
is_canceled = data["is_canceled"]
X_train,X_test,Y_train,Y_test = train_test_split(predictors,is_canceled,test_size=0.20,random_state=0)


X_train.shape


X_test.shape


Y_train.shape


Y_test.shape


#Определение лучшей модели


#Метод k-ближайших соседей


#k=7


knn = KNeighborsClassifier(n_neighbors=7)
knn.fit(X_train,Y_train)
Y_pred_knn=knn.predict(X_test)


Y_pred_knn.shape


score_knn_7 = round(accuracy_score(Y_pred_knn,Y_test)*100,2)

print("вычислить оценку точности: "+str(score_knn)+" %")


#k=4


knn_model=KNeighborsClassifier(n_neighbors=4).fit(X_train,Y_train)
knn_predictions=knn_model.predict(X_test)


CM=pd.crosstab(y_test,knn_predictions)
CM


k_range = range(1, 26)
scores = []
from sklearn import metrics
for k in k_range:
    knn = KNeighborsClassifier(n_neighbors=k)
    knn.fit(X_train, y_train)
    y_pred = knn.predict(X_test)
    scores.append(metrics.accuracy_score(y_test, y_pred))

print(scores)


TN=CM.iloc[0,0]
FP=CM.iloc[0,1]
FN=CM.iloc[1,0]
TP=CM.iloc[1,1]


#точность модели
score_knn_4=((TP+TN)*100)/(TP+TN+FP+FN)
score_knn_4


#ложноотрицательный показатель модели
fnr=FN*100/(FN+TP)
fnr


#Решающее дерево


#Строим модель на тренировочных данных и протестируем её на тестовых данных


C50_model = tree.DecisionTreeClassifier(criterion='entropy').fit(X_train, Y_train)
C50_Predictions = C50_model.predict(X_test)


CM = pd.crosstab(Y_test, C50_Predictions)
CM


TN=CM.iloc[0,0]
FP=CM.iloc[0,1]
FN=CM.iloc[1,0]
TP=CM.iloc[1,1]


#проверим точность модели
score_dt=((TP+TN)*100)/(TP+TN+FP+FN)
score_dt


fnr=FN*100/(FN+TP)
fnr


#Сравнение моделей


scores = [score_lr, score_knn]
algorithms = ["Decision Tree", "K-Nearest Neighbors"]    
for i in range(len(algorithms)):
    print("вычислить оценку точности:"+algorithms[i]+" is: "+str(scores[i])+" %")


sns.set(rc={'figure.figsize':(15,8)})
plt.xlabel("Алгоритм")
plt.ylabel("Точность")

sns.barplot(algorithms,scores)


#Достичь максимальной точности 85.24% можно с помощью решающего дерева
