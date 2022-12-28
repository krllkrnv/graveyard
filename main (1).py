import numpy as np
import time
import networkx as nx
import csv
import pandas as pd


def product(*args, repeat=25):
    pools = [tuple(pool) for pool in args] * repeat
    result = [[]]
    for pool in pools:
        result = [x+[y] for x in result for y in pool]
    for prod in result:
        yield tuple(prod)


def create_dataset():
    start_time = time.time()
    f = open('dataset.txt', 'w')
    f.write(' '.join(map(str, product(range(2)))))
    print("--- %s seconds ---" % (time.time() - start_time))
    f.close()
    with open('dataset.txt', 'r') as file:
        file_we_read = file.read()
        file_we_read = file_we_read.replace(') (', '\n')
        file_we_read = file_we_read.replace('(', '')
        file_we_read = file_we_read.replace(')', '')

    with open('dataset.txt', 'w') as file:
        file.write(file_we_read)


def prepare_and_slice():
    path = 'csv_dataset.csv'
    with open('dataset.txt') as f:
        data_arrays = np.fromstring(f.readline(), dtype=int, sep=',')
        check_trans = data_arrays
        check_trans = check_trans.reshape(5, 5)
        graph = nx.Graph(check_trans)
        data_trans = (int(nx.transitivity(graph)))
        all_data = np.append(data_arrays, data_trans)
        #header_list = ['first', 'second', 'third', '4th', 'transit']
        #df = pd.read_csv('csv_dataset.csv', names=header_list)
        #print(df)
        with open(path, 'a') as p:
            row_names = np.array(['1st', '2st', '3st', '4st', '5st', '6st', '7st', '8st', '9st', '10st', '11st', '12st',
                                  '13st', '14st', '15st', '16st', '17st', '18st', '19st', '20st',
                                  '21st', '22st', '23st', '24st', '25st', 'trn'])
            writer2 = csv.writer(p)
            writer2.writerow(row_names)
            writer = csv.writer(p)
            writer.writerow(all_data)
        for line in f:
            adj_arr = np.fromstring(line, dtype=int, sep=',')
            check_trans = adj_arr
            check_trans = check_trans.reshape(5, 5)
            graph = nx.Graph(check_trans)
            trans_cycle = (int(nx.transitivity(graph)))
            all_data = np.append(adj_arr, trans_cycle)
            with open(path, 'a') as p:
                writer = csv.writer(p)
                writer.writerow(all_data)
            #data_arrays = np.vstack([data_arrays, adj_arr])
            #data_trans = np.vstack([data_trans, trans_cycle])


val = input("create dataset? y/n")
if val == 'y':
    create_dataset()
elif val == 'n':
    print('ok!')

val = input("draw graph? y/n")
if val == 'y':
    prepare_and_slice()
elif val == 'n':
    print('ok!')


print('bye')

