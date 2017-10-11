//测试线程池
public class TestThreadPool {
    public static void main(String[] args)
    {
        // 创建3个线程的线程池
        ThreadPool t = ThreadPool.getThreadPool(3);
        t.execute(new Runnable[] { new Task(), new Task(), new Task() });
        t.execute(new Runnable[] { new Task(), new Task(), new Task() });
        System.out.println(t);
        System.out.println(t.getWorkThreadNumber());
        t.destroy();// 所有线程都执行完成才destory
        System.out.println(t);
    }

    // 任务类
    static class Task implements Runnable {
        private static volatile int i = 1;
        private int task_no;
        public Task()
        {
            task_no = i++;
        }

        @Override
        public void run()  // 执行任务
        {
            System.out.println("任务 " + task_no + " 开始");

            try {
                Thread.sleep((6 - task_no) * 1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            System.out.println("任务 " + task_no + " 完成");
        }
    }
}
