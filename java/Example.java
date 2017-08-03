public class Example {
    public static void main(String[] args){
        String str = "abcdef";
        int s = 3;
        char[] arr = str.toCharArray();
        char[] tmp = new char[s];
        Combine(arr, 0, arr.length - 1, tmp, s, s);
        //Permute(arr, 0, arr.length - 1);
    }
    public static void Combine(char[] arr, int left, int right, char[] tmp, int s, int remain) {
        if (remain == 0) {
            System.out.println("Combine:" + String.valueOf(tmp));
            //Permute(tmp, 0, s - 1);
            return;
        }
        for (int i = left; i <= right - remain + 1; ++i) {
            tmp[s - remain] = arr[i];
            Combine(arr, i + 1, right, tmp, s, remain - 1);
        }
    }
    public static void Permute(char[]arr, int low, int high) {
        if (low == high) {
            System.out.println(arr);
            return;
        }
        for (int i = low; i <= high; ++i) {
            char tmp;
            tmp = arr[i]; arr[i] = arr[low]; arr[low] = tmp;
            Permute(arr, low + 1, high);
            tmp = arr[i]; arr[i] = arr[low]; arr[low] = tmp;
        }
    }
}
