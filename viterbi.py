


def encode(input_array):
    state=[0,0,0,0]
    output=[]
    output_string = ""
    for i in input_array:
        state[0]=i
        output1=state[0]^state[1]^state[2]^state[3]
        output2=state[0]^state[2]^state[3]
        state.insert(0,state.pop())
        output_string+=str(output1)+str(output2)+" "
    print(output_string)


def main():
    input_list=list(input("Provide Input: "))
    input_list = list(map(int, input_list))
    #input_list = list(input_string)
    print(input_list)
    encode(input_list)

if __name__ == '__main__':
	main()
