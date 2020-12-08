#!/usr/bin/env python
# coding: utf-8


import numpy as np
import pandas as pd 
import matplotlib.pyplot as plt
import seaborn as sns 

import os
os.getcwd()


pd.read_csv('hotel_bookings.csv')



data = pd.read_csv("hotel_bookings.csv")



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


data.shape()

data.head()

data.tail()

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



data.info()



#Нет пропусков в данных

data.describe()




data.corr()



# ## Подготовка данных
# ### Обработка пустых значений 
# **Удаление строк с пропущенными значениями** 
# Удалить строки с пропусками можно с помощью команды data.dropna(inplace=True). Inplace - позволяет изменить текущую таблицу, иначе новые данные будут возвращены этой функцией. 
# Так как пропущенных значений мало мы просто удалим все строки с NaN значениями



data.dropna(inplace=True)
data.info()



# ### Обработка категориальных признаков
# **Кодируем столбец из категориального признака (Label Encoding)** 

from sklearn.preprocessing import LabelEncoder
label = LabelEncoder()
label.fit(data.is_canceled)
data.is_canceled = label.transform(data.is_canceled) 



data.is_canceled.head()


# **Нормализация признаков. Стандартное отклонение** 
    
from sklearn.preprocessing import StandardScaler
scale_features_std = StandardScaler()
features = data
features[:] = scale_features_std.fit_transform(data)
features 



features.mean()



# **Нормализация признаков. MinMax** 

from sklearn.preprocessing import MinMaxScaler
scale_features_mm = MinMaxScaler()
data[:] = scale_features_mm.fit_transform(data)
data



# **'Выделяем целевую переменную** 

target = data
train = data.drop(['is_repeated_guest', 'previous_cancellations',], axis=1) 



train.head()


# **'Выделяем тренировочную и тестовую выборки**
# y - целевая переменнная (target) 

from sklearn.model_selection import train_test_split
X_train, X_test, y_train, y_test = train_test_split(train, target, test_size = 0.3, random_state = 42)

N_train, _ = X_train.shape 
N_test,  _ = X_test.shape 
print (N_train, N_test)


# # Метод главных компонент (PCA) 

from sklearn.decomposition import PCA 
get_ipython().run_line_magic('matplotlib', 'inline')
import matplotlib.pyplot as plt 



pca = PCA()
pca.fit(X_train)
X_pca = pca.transform(X_train) 



for i, component in enumerate(pca.components_):
    print("{} component: {}% of initial variance".format(i + 1, round(100 * pca.explained_variance_ratio_[i], 2)))
    print(" + ".join("%.3f x %s" % (value, name)
for value, name in zip(component,train.columns))) 


plt.figure(figsize=(10,7))
plt.plot(np.cumsum(pca.explained_variance_ratio_), color='k', lw=2)
plt.axhline(0.9, c='r')
plt.axvline(9, c='b') 


# "Для описания 90% дисперсии данных достаточно 9-и компонент. 


data.to_csv(path_or_buf="h_bookings.csv", index=False) 

