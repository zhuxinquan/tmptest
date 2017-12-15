/**
 * Created by zxq on 17-12-7.
 */
//开启 4 个用户线程，其中 1 个线程大量占用 CPU 资源，其他 3 个线程则处于空闲状态
public class HoldCPUMain {
    public static class HoldCPUTask implements Runnable{

        @Override
        public void run() {
// TODO Auto-generated method stub
            while(true){
                System.out.println(1);
            }
        }

    }

    public static class LazyTask implements Runnable{

        @Override
        public void run() {
// TODO Auto-generated method stub
            while(true){
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
// TODO Auto-generated catch block
                    e.printStackTrace();
                }//空闲线程
            }
        }

    }


    public static void main(String[] args){
        for(int i=0;i<10;i++){
            new Thread(new HoldCPUTask()).start();
        }
    }
}