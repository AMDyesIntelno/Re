package ctf.stratumauhhur.libdroid;

import android.os.Bundle;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.util.Base64;
import android.view.View;
import java.io.BufferedReader;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.InputStreamReader;

public class a extends AppCompatActivity {
    static String a = a(getOperatingSystem(), 1);
    static String b = a(getPhoneNumber(), 1);
    static String c = a(installRootkit(), 1);
    static String d = a(generateConfusion(), 1);
    static Object f = a(obtainWorldDomination(), 1);
    static String flag = a(getFlag(), 1);
    static String g = a(installiOS(), 1);
    String e;

    public static native String generateConfusion();

    public static native String getFlag();

    public static native String getOperatingSystem();

    public static native String getPhoneNumber();

    public static native String installRootkit();

    public static native String installiOS();

    public static native String obtainWorldDomination();

    private static native void phoneHome(byte[] bArr, byte[] bArr2);

    /* access modifiers changed from: protected */
    @Override // android.support.v7.app.AppCompatActivity, android.support.v4.app.FragmentActivity, android.support.v4.app.BaseFragmentActivityDonut
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_a);
        try {
            a(a);
        } catch (Exception e2) {
        }
        this.e = "";
    }

    /* access modifiers changed from: package-private */
    public byte[] a(byte[] a0, String a1) {
        byte[] a2 = new byte[a0.length];
        for (char a3 = 0; a3 < a2.length; a3 = (char) (a3 + 1)) {
            a2[a3] = (byte) (a0[a3] ^ a1.charAt(a3 % a1.length()));
        }
        return a2;
    }

    public void a(View v) {
        if (v.getId() == R.id.button) {
            this.e += d.charAt(1);
        }
        if (v.getId() == R.id.button2) {
            this.e += d.charAt(2);
        }
        if (v.getId() == R.id.button3) {
            this.e += d.charAt(3);
        }
        if (v.getId() == R.id.button4) {
            this.e += d.charAt(4);
        }
        if (v.getId() == R.id.button5) {
            this.e += d.charAt(5);
        }
        if (v.getId() == R.id.button6) {
            this.e += d.charAt(6);
        }
        if (v.getId() == R.id.button7) {
            this.e += d.charAt(7);
        }
        if (v.getId() == R.id.button8) {
            this.e += d.charAt(8);
        }
        if (v.getId() == R.id.button9) {
            this.e += d.charAt(9);
        }
        if (v.getId() == R.id.button10) {
            this.e += d.charAt(0);
        }
        if (this.e.length() == 6 || v.getId() == R.id.button11) {
            String flag2 = flag;
            try {
                InputStream b2 = getAssets().open(g);
                ByteArrayOutputStream b22 = new ByteArrayOutputStream();
                byte[] data = new byte[16384];
                while (true) {
                    int nRead = b2.read(data, 0, data.length);
                    if (nRead == -1) {
                        break;
                    }
                    b22.write(data, 0, nRead);
                }
                b22.flush();
                byte[] j = b22.toByteArray();
                byte[] f_ = new byte[16];
                System.arraycopy((byte[]) f, 0, f_, 0, ((byte[]) f).length);
                System.arraycopy(this.e.getBytes(), 0, f_, 10, this.e.getBytes().length);
                phoneHome(j, f_);
                if (new String(j).startsWith(c)) {
                    flag2 = new String(j);
                }
            } catch (Exception e1) {
                e1.printStackTrace();
            }
            Snackbar.make(v, flag2, 0).setAction("Action", (View.OnClickListener) null).show();
            this.e = "";
        }
    }

    /* access modifiers changed from: package-private */
    public void a(String a2) throws Exception {
        InputStream b2 = getAssets().open(a2);
        ByteArrayOutputStream b22 = new ByteArrayOutputStream();
        byte[] data = new byte[16384];
        while (true) {
            int nRead = b2.read(data, 0, data.length);
            if (nRead == -1) {
                break;
            }
            b22.write(data, 0, nRead);
        }
        b22.flush();
        BufferedReader b4 = new BufferedReader(new InputStreamReader(new ByteArrayInputStream(a(b22.toByteArray(), b))));
        while (true) {
            String c2 = b4.readLine();
            if (c2 != null) {
                if (c2.startsWith(g)) {
                    g = c2.substring(g.length());
                }
                if (c2.startsWith((String) f)) {
                    f = Base64.decode(c2.substring(((String) f).length()), 0);
                }
            } else {
                return;
            }
        }
    }

    /* JADX INFO: Multiple debug info for r1v1 java.lang.String: [D('a1' java.lang.String), D('a1' java.lang.StringBuilder)] */
    static String a(String a2, int b2) {
        StackTraceElement a0 = new Exception().getStackTrace()[b2];
        StringBuilder a1 = new StringBuilder();
        a1.append(a0.getClassName()).insert(b2, a0.getMethodName());
        String a12 = a1.toString();
        char[] a22 = new char[a2.length()];
        char a4 = 0;
        char a3 = (char) a12.length();
        while (a4 < a2.length()) {
            a22[a4] = (char) (a12.charAt(a3 - 1) ^ (a2.charAt(a4) ^ 18));
            char a42 = (char) (a4 + 1);
            if (a42 >= a2.length()) {
                break;
            }
            a22[a42] = (char) (a12.charAt(a3 - 1) ^ (a2.charAt(a42) ^ 250));
            a4 = (char) (a42 + 1);
            a3 = (char) (a3 - 1);
            if (a3 <= 0) {
                a3 = (char) a12.length();
            }
        }
        return String.valueOf(a22);
    }

    static {
        System.loadLibrary("libdroid");
    }
}