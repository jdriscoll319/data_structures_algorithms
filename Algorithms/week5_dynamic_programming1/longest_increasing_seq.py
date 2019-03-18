
def lis(A):
    T = [None] * len(A)
    for i in range(len(A)):
        T[i] = 1
        for j in range( i ):
            if A[j] < A[i] and T[i] < T[j]+1:
                T[i] = T[j] + 1
                
    return (T)
A = [ 7 , 2 , 1 , 3 , 8 , 4 , 9 , 1 , 2 , 6 , 5 , 9 , 3, 8, 1]
print(A)
print(lis(A))
#print( [lis(A, i ) for i in range(len(A) )] ) 
