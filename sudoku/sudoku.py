#https://leetcode.cn/problems/valid-sudoku/
#https://leetcode.cn/problems/sudoku-solver/
import time
import copy

class Solution(object):
    def isValidSudoku(self, board):
        """
        :type board: List[List[str]]
        :rtype: bool
        """
        for i in range(0, 9):
            s = set()
            for j in range(0, 9):
                if board[i][j] != '.':
                    if board[i][j] in s: return False
                    s.add(board[i][j])
        for i in range(0, 9):
            s = set()
            for j in range(0, 9):
                if board[j][i] != '.':
                    if board[j][i] in s: return False
                    s.add(board[j][i])
        for block_i in range(0, 3):
            for block_j in range(0, 3):
                s = set()
                for i in range(block_i * 3, block_i * 3 + 3):
                    for j in range(block_j * 3, block_j * 3 + 3):
                        if board[i][j] == '.': continue
                        if board[i][j] in s: return False
                        s.add(board[i][j])
                        
        return True
    def getMatchItemsIndex(self, p1, p2):
        matchedList = []
        for i in range(0, 9):
            matchedList.append((p1, i))
            matchedList.append((i, p2))
        block_i = int(p1 / 3)
        block_j = int(p2 / 3)
        for i in range(block_i * 3, block_i * 3 + 3):
            for j in range(block_j * 3, block_j * 3 + 3):
                matchedList.append((i,j))
        return matchedList
    def getPossibleList(self, board):
        hasBlank = False
        possibleList = []
        failed = False
        for i in range(9):
            temp = []
            for j in range(9):
                temp.append([])
            possibleList.append(temp)
        for i in range(0, 9):
            for j in range(0, 9):
                s = set(["1","2","3","4","5","6","7","8","9"])
                if board[i][j] != '.': 
                    #possibleList[i][j] = [board[i][j]]
                    continue
                hasBlank = True
                indexList = self.getMatchItemsIndex(i,j)
                for item in indexList:
                    value=board[item[0]][item[1]]
                    if value != '.':
                        s.discard(value)
                possibleList[i][j] = list(sorted(s))
                #possibleList[i][j] = list(s)
                if len(s) == 0:
                    failed = True
        return possibleList, hasBlank, failed
    def solveSudoku(self, board):
        """
        :type board: List[List[str]]
        :rtype: None Do not return anything, modify board in-place instead.
        """
        while True:
            if not self.isValidSudoku(board): return
            #print("*" * 80)
            possibleList, hasBlank, failed = self.getPossibleList(board)
            can_continue = False
            min_len = 9
            m = {}
            if not hasBlank: break
            for i in range(0, 9):
                for j in range(0, 9):
                    l = len(possibleList[i][j])
                    if l > 0:
                        m[l] = m.get(l, []) + [[i,j]]
                    if(l < min_len and l > 0): min_len = l
                    if(len(possibleList[i][j]) == 1):
                        board[i][j]=possibleList[i][j][0]
                        can_continue = True
            time.sleep(0.1)
            if not can_continue: break
        print("solved\n" + "\n".join([" ".join(line) for line in board]))
    def solveSudokuNew(self, board, level = 1):
        """
        :type board: List[List[str]]
        :rtype: None Do not return anything, modify board in-place instead.
        """
        while True:
            if not self.isValidSudoku(board): 
                #print('not valid sudoku', level)
                return 0
            #time.sleep(0.01)
            #print("*" * 80)
            #print("level:{}".format(level))
            possibleList, hasBlank, failed = self.getPossibleList(board)
            if failed:
                #print("failed\n" + "\n".join([" ".join(line) for line in board]))
                return 0
            if not hasBlank: 
                #print("solved\n" + "\n".join([" ".join(line) for line in board]))
                return 1
            min_len = 9
            m = {}
            fill_list = []
            for i in range(0, 9):
                for j in range(0, 9):
                    l = len(possibleList[i][j])
                    if l > 0:
                        m[l] = m.get(l, []) + [[i,j]]
                    if(l < min_len and l > 0): min_len = l
                    if(len(possibleList[i][j]) == 1):
                        fill_list.append((i, j, possibleList[i][j][0]))
                        board[i][j]=possibleList[i][j][0]
            if(len(m)) == 0: 
                return 0
            for k in sorted(m.keys()):
                pass
                #print(k, m[k])
            min_key = sorted(m.keys())[0]
            if min_key == 1: 
                continue
            select = m[min_key][0]
            valid_count = 0
            for value in possibleList[select[0]][select[1]]:
                new_board = copy.deepcopy(board)
                new_board[select[0]][select[1]] = value
                #print("fill[{},{}] with {} level:{}\n".format(select[0], select[1], value, level) + str(possibleList[select[0]][select[1]]) + "\n" + "\n".join([" ".join(line) for line in new_board]))
                cnt = self.solveSudokuNew(new_board, level + 1)
                valid_count += cnt
            return valid_count

def init_board():
    return [["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]
    board = []
    board.append(["8", ".", ".", ".", ".", ".", ".", ".", "."])
    board.append([".", ".", "3", "6", ".", ".", ".", ".", "."])
    board.append([".", "7", ".", ".", "9", ".", "2", ".", "."])
    board.append([".", "5", ".", ".", ".", "7", ".", ".", "."])
    board.append([".", ".", ".", ".", "4", "5", "7", ".", "."])
    board.append([".", ".", ".", "1", ".", ".", ".", "3", "."])
    board.append([".", ".", "1", ".", ".", ".", ".", "6", "8"])
    board.append([".", ".", "8", "5", ".", ".", ".", "1", "."])
    board.append([".", "9", ".", ".", ".", ".", "4", ".", "."])
    return board

def main():
    s = Solution()
    board = init_board()
    print(s.solveSudokuNew(board))
    for i in range(0,9):
        for j in range(0,9):
            board = init_board()
            if board[i][j] == '.':continue
            board[i][j] = '.'
            print(i,j,s.solveSudokuNew(board))
    return
    board1 = [["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]
    print(s.isValidSudoku(board1))
    board2 = [["8","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]
    print(s.isValidSudoku(board2))
    #print(s.solveSudokuNew(board1))
    #print(s.solveSudokuNew(board2))
    board3 = []
    board3.append([".", "1", ".", ".", "7", "6", ".", ".", "."])
    board3.append(["8", ".", "5", ".", ".", ".", "3", ".", "."])
    board3.append([".", ".", ".", ".", ".", ".", ".", ".", "."])
    board3.append(["2", "7", ".", ".", ".", ".", ".", ".", "."])
    board3.append([".", ".", ".", "5", ".", ".", "1", ".", "."])
    board3.append(["6", ".", ".", ".", ".", ".", ".", ".", "."])
    board3.append([".", ".", "3", ".", ".", ".", ".", ".", "2"])
    board3.append([".", ".", ".", "9", ".", ".", ".", "4", "."])
    board3.append([".", ".", ".", ".", ".", ".", ".", "7", "6"])
    #print(s.isValidSudoku(board3))
    #print(s.solveSudoku(board3))
    #print(s.solveSudokuNew(board1))
    #print(s.solveSudokuNew(board3))
    board5 = []
    board5.append(["6", ".", ".", ".", ".", ".", "4", ".", "5"])
    board5.append([".", ".", "8", "2", ".", ".", ".", ".", "."])
    board5.append([".", ".", ".", ".", ".", ".", ".", ".", "."])
    board5.append([".", ".", ".", ".", ".", "6", ".", "1", "."])
    board5.append(["4", ".", "7", ".", ".", ".", ".", ".", "."])
    board5.append([".", ".", ".", "1", ".", ".", ".", "2", "."])
    board5.append([".", ".", "6", ".", ".", ".", "7", "8", "."])
    board5.append([".", ".", ".", ".", "5", "4", ".", ".", "."])
    board5.append([".", ".", ".", "9", ".", ".", ".", ".", "."])
    print(s.solveSudokuNew(board5))
    board5[8][3]='.'
    print(s.solveSudokuNew(board5))
    board4 = []
    board4.append([".", ".", ".", ".", ".", ".", ".", ".", "."])
    board4.append([".", ".", ".", ".", ".", ".", ".", ".", "."])
    board4.append([".", ".", ".", ".", ".", ".", ".", ".", "."])
    board4.append([".", ".", ".", ".", ".", ".", ".", ".", "."])
    board4.append([".", ".", ".", ".", ".", ".", ".", ".", "."])
    board4.append([".", ".", ".", ".", ".", ".", ".", ".", "."])
    board4.append([".", ".", ".", ".", ".", ".", ".", ".", "."])
    board4.append([".", ".", ".", ".", ".", ".", ".", ".", "."])
    board4.append([".", ".", ".", ".", ".", ".", ".", ".", "."])
    #print(s.solveSudokuNew(board4))

if __name__ == "__main__":
    main()
