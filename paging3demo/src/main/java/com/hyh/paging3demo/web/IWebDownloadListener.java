package com.hyh.paging3demo.web;

import android.webkit.WebView;


public interface IWebDownloadListener {

    void onDownloadStart(WebView webView, String url, String userAgent, String contentDisposition, String mimeType, long contentLength);

}
