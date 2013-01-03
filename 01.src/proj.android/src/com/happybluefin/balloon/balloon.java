package com.happybluefin.balloon;

import java.util.Locale;

import android.app.Application;
import android.util.Log;

public class balloon extends Application {
	
	private native int nativeSetLang(String a);
	
    public void onCreate() {

        //ȡ��������
//        mContext = this;

        //��ʼ����������
        _initLanguage();

        //��ʼ�����߲���
//        _loadOnlineConfig();

        //��ʼ�����а�
//        _initLeaderboards();
    }
    
    private void _initLanguage() {
		 String language1 = "";
		 String language2 = "";
		 
		 language1 = Locale.getDefault().getLanguage();
		 Log.i("jnitest", "------language1:-----"+language1);
		 language2 = Locale.getDefault().toString();
		 Log.i("jnitest", "------language2:-----"+language2);
		
		
		 if(language1.compareTo("zh") == 0)
			 nativeSetLang(language2);
		 else
			 nativeSetLang(language1); 
    }
    
    static {
        try {
            System.loadLibrary("game");
        }
        catch (UnsatisfiedLinkError e) {
            e.printStackTrace();
            throw e;
        }
    }
    
}