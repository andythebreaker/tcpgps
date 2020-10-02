package com.andythebreaker.tcpgps;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

//andythebreaker
import java.io.FileOutputStream;

import android.os.Environment;

import java.io.FileNotFoundException;
import java.io.File;
import java.io.OutputStream;

import android.provider.MediaStore;
import android.content.ContentValues;
import android.content.ContentResolver;
import android.net.Uri;

import java.io.InputStream;
import java.text.DateFormat;

import android.os.Bundle;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import java.nio.charset.StandardCharsets;

public class MainActivity extends AppCompatActivity {

    //https://fullmetal6927.pixnet.net/blog/post/204684237-%5Bandroid%5D-%5Bstudio%5D-socket-server%E6%8E%A5%E6%94%B6%E6%B8%AC%E8%A9%A6%E7%A8%8B%E5%BC%8F

    private static final int PORT = 9999;
    private List<Socket> mList = new ArrayList<Socket>();
    private volatile ServerSocket server = null;
    private ExecutorService mExecutorService = null; //線程
    private String hostip; //本機IP
    private TextView mText1;
    private TextView mText2;
    private Button mBut1 = null;
    private Handler myHandler = null;
    private volatile boolean flag = true;//线程标志位
    private Handler handler = new Handler();//andythebreaker 原本 no static   OKOKOK
    String s;

    private TextView abtext;
    private Button abbton = null;
    private static final String where_to_storge = "/storage/sdcard1";
    //private static final String TEST_PATH = "/storage/extSdCard/MediaWriteTest";

    private final File baseDir = new File(where_to_storge);
    private DateFormat dateFormat;
    private DateFormat timeFormat;
    private static final String TAG = "MediaWrite";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        this.requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.activity_main);
        hostip = getLocalIpAddress();  //獲取本機IP

        mText1 = (TextView) findViewById(R.id.textView1);
        mText1.setText(hostip);
        mText1.setEnabled(false);

        abtext = (TextView) findViewById(R.id.textView3);
        abtext.setText("abtext");
        abtext.setEnabled(true);
        abbton = (Button) findViewById(R.id.button);
        abbton.setOnClickListener(new abbtonClickListener());

        mText2 = (TextView) findViewById(R.id.textView2);

        mBut1 = (Button) findViewById(R.id.but1);
        mBut1.setOnClickListener(new Button1ClickListener());
        //取得非UI線程傳來的msg，以改變介面
        myHandler = new Handler() {
            @SuppressLint("HandlerLeak")
            public void handleMessage(Message msg) {
                if (msg.what == 0x1234) {
                    mText2.append("\n" + msg.obj.toString());
                }
            }
        };

    }

    private final class abbtonClickListener implements View.OnClickListener {
        @
                Override
        public void onClick(View v) {
            //String isExternalStorageReadable_str = (isExternalStorageReadable())?"可讀":"不可讀";
            //String isExternalStorageWritable_str= (isExternalStorageWritable())?"可寫":"不可寫";
            //abtext.setText(isExternalStorageReadable_str+isExternalStorageWritable_str);
            /*if (writefile44()) {
                abtext.setText("OK!");
            }*/
            //abtext.setText(Environment.getExternalStorageDirectory().toString());
            check_length_file();
            /*try {
                abtext.setText(implementMFread("tcpgps_length.txt"));
            } catch (IOException e) {
                abtext.setText(e.toString());
            }*/
            runCreateTests();
        }
    }

    //對button1的監聽事件
    private final class Button1ClickListener implements View.OnClickListener {
        @Override
        public void onClick(View v) {
            // TODO Auto-generated method stub
            //如果是「啟動」，證明服務器是關閉狀態，可以開啟服務器
            if (mBut1.getText().toString().equals("啟動")) {
                ServerThread serverThread = new ServerThread();
                flag = true;
                serverThread.start();
                mBut1.setText("關閉");
                mText1.setText(getLocalIpAddress());
                //show IP address
                Toast toast = Toast.makeText(MainActivity.this, "IP address: " + getLocalIpAddress(), Toast.LENGTH_LONG);
                toast.show();
            } else {
                try {
                    flag = false;
                    server.close();
                    for (int p = 0; p < mList.size(); p++) {
                        Socket s = mList.get(p);
                        s.close();
                    }
                    mExecutorService.shutdownNow();
                    mBut1.setText("啟動");
                    mText1.setText("Not Connect");
                    Log.v("Socket-status", "服務器已關閉");
                } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }
        }
    }

    //Server端的主線程
    class ServerThread extends Thread {
        public void run() {
            try {
                server = new ServerSocket(PORT);
            } catch (IOException e1) {
                e1.printStackTrace();
            }
            mExecutorService = Executors.newCachedThreadPool();  //創建一個線程
            Socket client = null;
            while (flag) {
                try {
                    Log.v("test", String.valueOf(flag));
                    client = server.accept();
                    handler.post(new Runnable() {
                        public void run() {
                            mText1.setText("Connected.");
                        }
                    });
                    try {
                        handler.post(new Runnable() {
                            public void run() {
                                mText2.setText(s);  //post message on the textView
                            }
                        });
                    } catch (Exception e) {
                        handler.post(new Runnable() {
                            public void run() {
                                mText2.setText(s);
                            }
                        });
                    }
                    //把客户端放入客户端集合中
                    mList.add(client);
                    mExecutorService.execute(new Service(client)); //啟動一個新的線程來處理連接
                } catch (IOException e) {
                    e.printStackTrace();
                    handler.post(new Runnable() {
                        public void run() {
                            mText2.setText("disConncet");
                        }
                    });
                }
            }
        }
    }

    //獲取本地IP
    @SuppressLint("LongLogTag")
    public static String getLocalIpAddress() {
        try {
            for (Enumeration<NetworkInterface> en = NetworkInterface
                    .getNetworkInterfaces(); en.hasMoreElements(); ) {
                NetworkInterface intf = en.nextElement();
                for (Enumeration<InetAddress> enumIpAddr = intf
                        .getInetAddresses(); enumIpAddr.hasMoreElements(); ) {
                    InetAddress inetAddress = enumIpAddr.nextElement();
                    if (!inetAddress.isLoopbackAddress() && !inetAddress.isLinkLocalAddress()) {
                        return inetAddress.getHostAddress().toString();
                    }
                }
            }
        } catch (SocketException ex) {
            Log.e("WifiPreference IpAddress", ex.toString());
        }
        return null;
    }

    //處理與client對話的線程
    class Service implements Runnable {
        private volatile boolean kk = true;
        private Socket socket;
        private BufferedReader in = null;
        private String msg = "";

        public Service(Socket socket) {
            this.socket = socket;   //reada6
            try {
                in = new BufferedReader(new InputStreamReader(socket.getInputStream(), "UTF-8"));
                msg = "OK";   //reada8
                this.sendmsg(msg);  //reada9
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        public void run() {
            while (kk) {
                try {
                    if ((msg = in.readLine()) != null) {
                        //當客戶端發送的訊息為：exit時，關閉連接
                        if (msg.equals("exit")) {
                            mList.remove(socket);
                            break;
                            //接收客户端發過來的訊息msg，然後發送給客戶端。
                        } else {
                            Message msgLocal = new Message();
                            msgLocal.what = 0x1234;
                            msgLocal.obj = msg + " （From Client）";

                            System.out.println(msgLocal.obj.toString());
                            System.out.println(msg);
                            myHandler.sendMessage(msgLocal);
                            msg = socket.getInetAddress() + ":" + msg + "（From Server）";
                            this.sendmsg(msg);
                        }
                    }
                } catch (IOException e) {
                    System.out.println("close");
                    kk = false;
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }
        }

        //向客戶端發送訊息
        public void sendmsg(String msg) {
            System.out.println(msg);
            PrintWriter pout = null;
            try {
                pout = new PrintWriter(new BufferedWriter(
                        new OutputStreamWriter(socket.getOutputStream())), true);
                pout.println(msg);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    //andythebreaker   sd card

    boolean isExternalStorageReadable() {
        return Environment.getExternalStorageDirectory().canRead();
    }

    boolean isExternalStorageWritable() {
        boolean writable;
        final String filePath = Environment.getExternalStorageDirectory() +
                "/" + "testExternalStorageWritableFile";
        FileOutputStream fos = null;
        try {
            fos = new FileOutputStream(filePath);
            writable = true;
            // delete test file
            File file = new File(filePath);
            file.delete();
        } catch (FileNotFoundException e) {
            writable = false;
        } finally {
            if (fos != null)
                try {
                    fos.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
        }
        return writable;
    }

    //http://brianyeh.blogspot.com/2015/01/android.html
    boolean writefile44() {

        boolean writOK;
        final String filePath = where_to_storge +
                "/" + "tcpgpu.txt";
        FileOutputStream fos = null;
        try {
            fos = new FileOutputStream(filePath);
            writOK = true;
            // delete test file
            File file = new File(filePath);/*
            String inputString = "Hello World!";
            byte[] byteArrray = inputString.getBytes();
            try{
            fos.write(byteArrray);
            }catch(IOException e) {
                e.printStackTrace();
            }*/
            //file.delete();
        } catch (FileNotFoundException e) {
            writOK = false;
            abtext.setText(e.toString());
        } finally {
            if (fos != null)
                try {
                    fos.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
        }
        return writOK;
    }


    public class MediaFile {

        private final File file;
        private final ContentResolver contentResolver;
        private final Uri filesUri;
        private final Uri imagesUri;

        public MediaFile(ContentResolver contentResolver, File file) {
            this.file = file;
            this.contentResolver = contentResolver;
            filesUri = MediaStore.Files.getContentUri("external");
            imagesUri = MediaStore.Images.Media.EXTERNAL_CONTENT_URI;
        }

        /**
         * Deletes the file. Returns true if the file has been successfully deleted or otherwise does not exist. This operation is not
         * recursive.
         */
        public boolean delete()
                throws IOException {
            if (!file.exists()) {
                return true;
            }

            boolean directory = file.isDirectory();
            if (directory) {
                // Verify directory does not contain any files/directories within it.
                String[] files = file.list();
                if (files != null && files.length > 0) {
                    return false;
                }
            }

            String where = MediaStore.MediaColumns.DATA + "=?";
            String[] selectionArgs = new String[]{file.getAbsolutePath()};

            // Delete the entry from the media database. This will actually delete media files (images, audio, and video).
            contentResolver.delete(filesUri, where, selectionArgs);

            if (file.exists()) {
                // If the file is not a media file, create a new entry suggesting that this location is an image, even
                // though it is not.
                ContentValues values = new ContentValues();
                values.put(MediaStore.Files.FileColumns.DATA, file.getAbsolutePath());
                contentResolver.insert(imagesUri, values);

                // Delete the created entry, such that content provider will delete the file.
                contentResolver.delete(filesUri, where, selectionArgs);
            }

            return !file.exists();
        }

        public File getFile() {
            return file;
        }

        /**
         * Creates a new directory. Returns true if the directory was successfully created or exists.
         */
        public boolean mkdir()
                throws IOException {
            if (file.exists()) {
                return file.isDirectory();
            }

            ContentValues values;
            Uri uri;

            // Create a media database entry for the directory. This step will not actually cause the directory to be created.
            values = new ContentValues();
            values.put(MediaStore.Files.FileColumns.DATA, file.getAbsolutePath());
            contentResolver.insert(filesUri, values);

            // Create an entry for a temporary image file within the created directory.
            // This step actually causes the creation of the directory.
            values = new ContentValues();
            values.put(MediaStore.Files.FileColumns.DATA, file.getAbsolutePath() + "/temp.jpg");
            uri = contentResolver.insert(imagesUri, values);

            // Delete the temporary entry.
            contentResolver.delete(uri, null, null);

            return file.exists();
        }

        /**
         * Returns an OutputStream to write to the file. The file will be truncated immediately.
         */
        public OutputStream write()
                throws IOException {
            if (file.exists() && file.isDirectory()) {
                throw new IOException("File exists and is a directory.");
            }

            // Delete any existing entry from the media database.
            // This may also delete the file (for media types), but that is irrelevant as it will be truncated momentarily in any case.
            String where = MediaStore.MediaColumns.DATA + "=?";
            String[] selectionArgs = new String[]{file.getAbsolutePath()};
            contentResolver.delete(filesUri, where, selectionArgs);

            ContentValues values = new ContentValues();
            values.put(MediaStore.Files.FileColumns.DATA, file.getAbsolutePath());
            Uri uri = contentResolver.insert(filesUri, values);

            if (uri == null) {
                // Should not occur.
                throw new IOException("Internal error.");
            }

            return contentResolver.openOutputStream(uri,"wa");
        }

        public InputStream read() throws IOException {
            if (file.exists() && file.isDirectory()) {
                throw new IOException("File exists and is a directory.");
            }

            // Delete any existing entry from the media database.
            // This may also delete the file (for media types), but that is irrelevant as it will be truncated momentarily in any case.
            String where = MediaStore.MediaColumns.DATA + "=?";
            String[] selectionArgs = new String[]{file.getAbsolutePath()};
            contentResolver.delete(filesUri, where, selectionArgs);

            ContentValues values = new ContentValues();
            values.put(MediaStore.Files.FileColumns.DATA, file.getAbsolutePath());
            Uri uri = contentResolver.insert(filesUri, values);

            if (uri == null) {
                // Should not occur.
                throw new IOException("Internal error.");
            }

            return contentResolver.openInputStream(uri);
        }
    }

    //https://forum.xda-developers.com/showthread.php?t=2634840
    private void testCreateFile(String path, String assetPath)
            throws IOException {
        // Create File "Hello.txt"
        File file = new File(baseDir, path);
        abtext.setText(abtext.getText() + ("Writing trivial text file: " + file.getAbsolutePath()) + "\n");
        abtext.setText(abtext.getText() + ("* Prewrite state: " + getFileState(file)) + "\n");

        MediaFile mf = new MediaFile(getContentResolver(), file);
        //InputStream in = getAssets().open(assetPath);
        //write(byte[] b, int off, int len)XXXXXXXXXXXx
        OutputStream out = mf.write();
        //byte[] buffer = new byte[4096];
        //int bytesRead;
        //while ((bytesRead = in.read(buffer)) != -1) {
        //out.write(buffer, 0, bytesRead);
        //}
        //String Last_length_of_external_read = new String(buffer, StandardCharsets.UTF_8);
        //int Last_length_of_external_read_INT = Integer.valueOf(Last_length_of_external_read);
        int Last_length_of_external_read_INT = Integer.valueOf(implementMFread(assetPath).replaceAll("[^0-9]", ""));/*TODO:
        E/AndroidRuntime: FATAL EXCEPTION: main
    Process: com.andythebreaker.tcpgps, PID: 9135
    java.lang.NumberFormatException: Invalid int: "6699673266996765"
    */
        //in.close();
        String inputString = "this is what i want to sayyyyyyy\n";
        byte[] byteArrray = inputString.getBytes();
        /*length :
Arrays (int[], double[], String[]) — 取得Array的長度
length():
String related Object (String, StringBuilder, etc) — 取得字串的長度
size():
Collection Object (ArrayList, Set, etc) — 取得集合物件相關大小*/
        write_length(byteArrray.length + Last_length_of_external_read_INT);
        //out.write(byteArrray, Last_length_of_external_read_INT, byteArrray.length);
        out.write(byteArrray);
        out.close();
        abtext.setText(abtext.getText() + ("* Postwrite state: " + getFileState(file)) + "\n");
    }

    private String getFileState(File file) {
        if (!file.exists()) {
            return ("[DOES NOT EXIST] " + file.getAbsolutePath());
        }

        StringBuilder out = new StringBuilder();

        if (file.isDirectory()) {
            out.append("[DIR] ");
        } else {
            out.append("[FILE] ");
        }
        out.append(file.getAbsolutePath());
        out.append(' ');

        if (file.isDirectory()) {
            String[] items = file.list();
            out.append(" Items: ");
            out.append(items == null ? 0 : items.length);
        }

        long lastModified = file.lastModified();
        try {
            if (lastModified != 0) {
                out.append(" Last Modified: ");
                out.append(dateFormat.format(lastModified));
                out.append(' ');
                out.append(timeFormat.format(lastModified));
            }
        } catch (java.lang.NullPointerException e) {
            abtext.setText(abtext.getText() + "java.lang.NullPointerException" + e.toString());
        }


        if (!file.isDirectory()) {
            out.append(" Size: " + file.length());
        }

        return out.toString();
    }

    private void runCreateTests() {
        abtext.setText(abtext.getText() + ("---------------------------------") + "\n");
        abtext.setText(abtext.getText() + ("Create Test"));
        abtext.setText(abtext.getText() + ("---------------------------------") + "\n");
        if (!baseDir.exists() || !baseDir.isDirectory()) {
            abtext.setText(abtext.getText() + ("Base directory does not exist: aborting") + "\n");
            return;
        }
        try {
            testCreateFile("tcpgps_run1.txt", "tcpgps_length.txt");
            //testMkDir("Stuff");
            //testCreateFile("Hi.txt", "hello.txt");
            //testCreateFile("FX.png", "FX.png");
        } catch (IOException ex) {
            abtext.setText(abtext.getText() + ("Create test failed." + ex) + "\n");
            Log.w(TAG, "Failed to create directory.", ex);
        }
    }


    private void write_length(int length_number) {
        abtext.setText(abtext.getText() + ("---------------------------------"));
        abtext.setText(abtext.getText() + ("write_length..."));
        abtext.setText(abtext.getText() + ("---------------------------------") + "\n");
        if (!baseDir.exists() || !baseDir.isDirectory()) {
            abtext.setText(abtext.getText() + ("Base directory does not exist: aborting") + "\n");
            return;
        }
        try {
            String length_path = "tcpgps_length.txt";
            File file = new File(baseDir, length_path);
            abtext.setText(abtext.getText() + ("Writing trivial text file: " + file.getAbsolutePath()) + "\n");
            abtext.setText(abtext.getText() + ("* Prewrite state: " + getFileState(file)) + "\n");

            MediaFile mf = new MediaFile(getContentResolver(), file);
            OutputStream out = mf.write();
            String inputString = Integer.toString(length_number);
            byte[] byteArrray = inputString.getBytes();
            out.write(byteArrray);
            out.close();
            abtext.setText(abtext.getText() + ("* Postwrite state: " + getFileState(file)) + "\n");
        } catch (IOException ex) {
            abtext.setText(abtext.getText() + ("Create test failed." + ex) + "\n");
            Log.w(TAG, "Failed to create directory.", ex);
        }
    }
    /*private void testMkDir(String path)
            throws IOException {
        File file = new File(baseDir, path);
        log("MkDir: " + file.getAbsolutePath());
        log("* Prewrite state: " + getFileState(file));
        MediaFile mf = new MediaFile(getContentResolver(), file);
        boolean mkdir = mf.mkdir();
        log("* mkdir() result: " + mkdir);
        log("* Postwrite state: " + getFileState(file));
    }*/

    private void check_length_file() {
        abtext.setText(abtext.getText() + ("---------------------------------"));
        abtext.setText(abtext.getText() + ("check_length_file..."));
        abtext.setText(abtext.getText() + ("---------------------------------") + "\n");
        if (!baseDir.exists() || !baseDir.isDirectory()) {
            abtext.setText(abtext.getText() + ("Base directory does not exist: aborting") + "\n");
            return;
        }
        try {
            String length_path = "tcpgps_length.txt";
            File file = new File(baseDir, length_path);
            abtext.setText(abtext.getText() + ("Writing trivial text file: " + file.getAbsolutePath()) + "\n");
            String getFileState_file = getFileState(file);
            if (getFileState_file.contains("[DOES NOT EXIST] ")) {
                abtext.setText(abtext.getText() + ("* Prewrite state: " + getFileState_file) + "\n");
                MediaFile mf = new MediaFile(getContentResolver(), file);
                OutputStream out = mf.write();
                String inputString = Integer.toString(0);
                byte[] byteArrray = inputString.getBytes();
                out.write(byteArrray);
                out.close();
                abtext.setText(abtext.getText() + ("* Postwrite state: " + getFileState(file)) + "\n");
            } else {
                abtext.setText("length file EXIST!!\n");
            }
        } catch (IOException ex) {
            abtext.setText(abtext.getText() + ("Create test failed." + ex) + "\n");
            Log.w(TAG, "Failed to create directory.", ex);
        }
    }

    private String implementMFread(String path) throws IOException {
        File file = new File(baseDir, path);
        abtext.setText(abtext.getText() + ("READing file: " + file.getAbsolutePath()) + "::");
        abtext.setText(abtext.getText() + ("* state: " + getFileState(file)) + "\n");
        MediaFile mf = new MediaFile(getContentResolver(), file);
        InputStream in = mf.read();
        byte[] buffer = new byte[4096];
        int bytesRead;
        while ((bytesRead = in.read(buffer)) != -1) {
            //out.write(buffer, 0, bytesRead);
        }
        String WhatIRead = new String(buffer, StandardCharsets.UTF_8);
        abtext.setText(abtext.getText() + (" ! Read the result: " + WhatIRead) + "\n");
        return WhatIRead;
    }
}