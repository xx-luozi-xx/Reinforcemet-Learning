import matplotlib.pyplot as plt

file_path = './save/Winning_Rage_'

def read_and_plot(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()

    # 处理第一组数据
    n = int(lines[0].strip())  # 读取第一组数据的数量
    a_values = list(map(float, lines[1].strip().split(' ')))  # 读取第一组的数据点

    # 处理第二组数据
    m = int(lines[2].strip())  # 读取第二组数据的数量
    b_values = list(map(float, lines[3].strip().split(' ')))  # 读取第二组的数据点

    # 确保数据点的数量正确
    assert n == len(a_values), "The number of elements in the first set does not match."
    assert m == len(b_values), "The number of elements in the second set does not match."
    assert n == m
    # 计算平局数据
    c_values = [1-(a + b) for a, b in zip(a_values, b_values)]
    
    # 绘制折线图
    x_values = list(range(1, n+1))
    plt.figure(figsize=(12, 6))
    plt.plot(x_values, a_values, marker='o', linestyle='-', label='Black win')
    plt.plot(x_values, b_values, marker='x', linestyle='-', label='White win')
    plt.plot(x_values, c_values, marker='s', linestyle='-', label='Draw')
    plt.title('Winning Rate')
    plt.xlabel('Round(x1k)')
    plt.ylabel('Rate')
    plt.legend()  # 显示图例
    plt.grid(True)
    plt.show()

# 调用函数，传入文件路径

for i in range(0, 2):
    read_and_plot(file_path+str(i))
