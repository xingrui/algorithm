public class Example {
    public static void main(String[] args){
        String str = "abcdef";
        int s = 3;
        char[] arr = str.toCharArray();
        char[] tmp = new char[s];
        Combine(arr, 0, arr.length, tmp, s, s);
    }
    public static void Combine(char[] arr, int left, int right, char[] tmp, int s, int remain) {
        if (remain == 0) {
            System.out.println(String.valueOf(tmp));
            return;
        }
        for (int i = left; i < right - remain + 1; ++i) {
            tmp[s - remain] = arr[i];
            Combine(arr, i + 1, right, tmp, s, remain - 1);
        }
    }
}
