#include "widget.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QUrl>
#include <QByteArray>
#include <QFileDialog>
#include <QMessageBox>

static const char * g_ext_to_content_type[] = {
    ".001","application/x-001"
    ,".301","application/x-301"
    ,".323","text/h323"
    ,".906","application/x-906"
    ,".907","drawing/907"
    ,".a11","application/x-a11"
    ,".acp","audio/x-mei-aac"
    ,".ai","application/postscript"
    ,".aif","audio/aiff"
    ,".aifc","audio/aiff"
    ,".aiff","audio/aiff"
    ,".anv","application/x-anv"
    ,".asa","text/asa"
    ,".asf","video/x-ms-asf"
    ,".asp","text/asp"
    ,".asx","video/x-ms-asf"
    ,".au","audio/basic"
    ,".avi","video/avi"
    ,".awf","application/vnd.adobe.workflow"
    ,".biz","text/xml"
    ,".bmp","application/x-bmp"
    ,".bot","application/x-bot"
    ,".c4t","application/x-c4t"
    ,".c90","application/x-c90"
    ,".cal","application/x-cals"
    ,".cat","application/vnd.ms-pki.seccat"
    ,".cdf","application/x-netcdf"
    ,".cdr","application/x-cdr"
    ,".cel","application/x-cel"
    ,".cer","application/x-x509-ca-cert"
    ,".cg4","application/x-g4"
    ,".cgm","application/x-cgm"
    ,".cit","application/x-cit"
    ,".class","java/*"
    ,".cml","text/xml"
    ,".cmp","application/x-cmp"
    ,".cmx","application/x-cmx"
    ,".cot","application/x-cot"
    ,".conf","text/plain"
    ,".crl","application/pkix-crl"
    ,".crt","application/x-x509-ca-cert"
    ,".csi","application/x-csi"
    ,".css","text/css"
    ,".cut","application/x-cut"
    ,".dbf","application/x-dbf"
    ,".dbm","application/x-dbm"
    ,".dbx","application/x-dbx"
    ,".dcd","text/xml"
    ,".dcx","application/x-dcx"
    ,".der","application/x-x509-ca-cert"
    ,".dgn","application/x-dgn"
    ,".dib","application/x-dib"
    ,".dll","application/x-msdownload"
    ,".doc","application/msword"
    ,".dot","application/msword"
    ,".drw","application/x-drw"
    ,".dtd","text/xml"
    ,".dwf","Model/vnd.dwf"
    ,".dwf","application/x-dwf"
    ,".dwg","application/x-dwg"
    ,".dxb","application/x-dxb"
    ,".dxf","application/x-dxf"
    ,".edn","application/vnd.adobe.edn"
    ,".emf","application/x-emf"
    ,".eml","message/rfc822"
    ,".ent","text/xml"
    ,".epi","application/x-epi"
    ,".eps","application/x-ps"
    ,".eps","application/postscript"
    ,".etd","application/x-ebx"
    ,".exe","application/x-msdownload"
    ,".fax","image/fax"
    ,".fdf","application/vnd.fdf"
    ,".fif","application/fractals"
    ,".fo","text/xml"
    ,".frm","application/x-frm"
    ,".g4","application/x-g4"
    ,".gbr","application/x-gbr"
    ,".gcd","application/x-gcd"
    ,".gif","image/gif"
    ,".gl2","application/x-gl2"
    ,".gp4","application/x-gp4"
    ,".hgl","application/x-hgl"
    ,".hmr","application/x-hmr"
    ,".hpg","application/x-hpgl"
    ,".hpl","application/x-hpl"
    ,".hqx","application/mac-binhex40"
    ,".hrf","application/x-hrf"
    ,".hta","application/hta"
    ,".htc","text/x-component"
    ,".htm","text/html"
    ,".html","text/html"
    ,".htt","text/webviewhtml"
    ,".htx","text/html"
    ,".icb","application/x-icb"
    ,".ico","image/x-icon"
    ,".ico","application/x-ico"
    ,".iff","application/x-iff"
    ,".ig4","application/x-g4"
    ,".igs","application/x-igs"
    ,".iii","application/x-iphone"
    ,".img","application/x-img"
    ,".ini","text/plain"
    ,".ins","application/x-internet-signup"
    ,".isp","application/x-internet-signup"
    ,".IVF","video/x-ivf"
    ,".java","java/*"
    ,".jfif","image/jpeg"
    ,".jpe","image/jpeg"
    ,".jpe","application/x-jpe"
    ,".jpeg","image/jpeg"
    ,".jpg","image/jpeg"
    ,".jpg","application/x-jpg"
    ,".js","application/x-javascript"
    ,".jsp","text/html"
    ,".la1","audio/x-liquid-file"
    ,".lar","application/x-laplayer-reg"
    ,".latex","application/x-latex"
    ,".lavs","audio/x-liquid-secure"
    ,".lbm","application/x-lbm"
    ,".lmsff","audio/x-la-lms"
    ,".log","text/plain"
    ,".ls","application/x-javascript"
    ,".ltr","application/x-ltr"
    ,".m1v","video/x-mpeg"
    ,".m2v","video/x-mpeg"
    ,".m3u","audio/mpegurl"
    ,".m4e","video/mpeg4"
    ,".mac","application/x-mac"
    ,".man","application/x-troff-man"
    ,".math","text/xml"
    ,".mdb","application/msaccess"
    ,".mdb","application/x-mdb"
    ,".mfp","application/x-shockwave-flash"
    ,".mht","message/rfc822"
    ,".mhtml","message/rfc822"
    ,".mi","application/x-mi"
    ,".mid","audio/mid"
    ,".midi","audio/mid"
    ,".mil","application/x-mil"
    ,".mml","text/xml"
    ,".mnd","audio/x-musicnet-download"
    ,".mns","audio/x-musicnet-stream"
    ,".mocha","application/x-javascript"
    ,".movie","video/x-sgi-movie"
    ,".mp1","audio/mp1"
    ,".mp2","audio/mp2"
    ,".mp2v","video/mpeg"
    ,".mp3","audio/mp3"
    ,".mp4","video/mpeg4"
    ,".mpa","video/x-mpg"
    ,".mpd","application/vnd.ms-project"
    ,".mpe","video/x-mpeg"
    ,".mpeg","video/mpg"
    ,".mpg","video/mpg"
    ,".mpga","audio/rn-mpeg"
    ,".mpp","application/vnd.ms-project"
    ,".mps","video/x-mpeg"
    ,".mpt","application/vnd.ms-project"
    ,".mpv","video/mpg"
    ,".mpv2","video/mpeg"
    ,".mpw","application/vnd.ms-project"
    ,".mpx","application/vnd.ms-project"
    ,".mtx","text/xml"
    ,".mxp","application/x-mmxp"
    ,".net","image/pnetvue"
    ,".nrf","application/x-nrf"
    ,".nws","message/rfc822"
    ,".odc","text/x-ms-odc"
    ,".out","application/x-out"
    ,".p10","application/pkcs10"
    ,".p12","application/x-pkcs12"
    ,".p7b","application/x-pkcs7-certificates"
    ,".p7c","application/pkcs7-mime"
    ,".p7m","application/pkcs7-mime"
    ,".p7r","application/x-pkcs7-certreqresp"
    ,".p7s","application/pkcs7-signature"
    ,".pc5","application/x-pc5"
    ,".pci","application/x-pci"
    ,".pcl","application/x-pcl"
    ,".pcx","application/x-pcx"
    ,".pdf","application/pdf"
    ,".pdf","application/pdf"
    ,".pdx","application/vnd.adobe.pdx"
    ,".pfx","application/x-pkcs12"
    ,".pgl","application/x-pgl"
    ,".pic","application/x-pic"
    ,".pko","application/vnd.ms-pki.pko"
    ,".pl","application/x-perl"
    ,".plg","text/html"
    ,".pls","audio/scpls"
    ,".plt","application/x-plt"
    ,".png","image/png"
    ,".png","application/x-png"
    ,".pot","application/vnd.ms-powerpoint"
    ,".ppa","application/vnd.ms-powerpoint"
    ,".ppm","application/x-ppm"
    ,".pps","application/vnd.ms-powerpoint"
    ,".ppt","application/vnd.ms-powerpoint"
    ,".ppt","application/x-ppt"
    ,".pr","application/x-pr"
    ,".prf","application/pics-rules"
    ,".prn","application/x-prn"
    ,".prt","application/x-prt"
    ,".ps","application/x-ps"
    ,".ps","application/postscript"
    ,".ptn","application/x-ptn"
    ,".pwz","application/vnd.ms-powerpoint"
    ,".r3t","text/vnd.rn-realtext3d"
    ,".ra","audio/vnd.rn-realaudio"
    ,".ram","audio/x-pn-realaudio"
    ,".ras","application/x-ras"
    ,".rat","application/rat-file"
    ,".rdf","text/xml"
    ,".rec","application/vnd.rn-recording"
    ,".red","application/x-red"
    ,".rgb","application/x-rgb"
    ,".rjs","application/vnd.rn-realsystem-rjs"
    ,".rjt","application/vnd.rn-realsystem-rjt"
    ,".rlc","application/x-rlc"
    ,".rle","application/x-rle"
    ,".rm","application/vnd.rn-realmedia"
    ,".rmf","application/vnd.adobe.rmf"
    ,".rmi","audio/mid"
    ,".rmj","application/vnd.rn-realsystem-rmj"
    ,".rmm","audio/x-pn-realaudio"
    ,".rmp","application/vnd.rn-rn_music_package"
    ,".rms","application/vnd.rn-realmedia-secure"
    ,".rmvb","application/vnd.rn-realmedia-vbr"
    ,".rmx","application/vnd.rn-realsystem-rmx"
    ,".rnx","application/vnd.rn-realplayer"
    ,".rp","image/vnd.rn-realpix"
    ,".rpm","audio/x-pn-realaudio-plugin"
    ,".rsml","application/vnd.rn-rsml"
    ,".rt","text/vnd.rn-realtext"
    ,".rtf","application/msword"
    ,".rtf","application/x-rtf"
    ,".rv","video/vnd.rn-realvideo"
    ,".sam","application/x-sam"
    ,".sat","application/x-sat"
    ,".sdp","application/sdp"
    ,".sdw","application/x-sdw"
    ,".sit","application/x-stuffit"
    ,".slb","application/x-slb"
    ,".sld","application/x-sld"
    ,".slk","drawing/x-slk"
    ,".smi","application/smil"
    ,".smil","application/smil"
    ,".smk","application/x-smk"
    ,".snd","audio/basic"
    ,".sol","text/plain"
    ,".sor","text/plain"
    ,".spc","application/x-pkcs7-certificates"
    ,".spl","application/futuresplash"
    ,".spp","text/xml"
    ,".ssm","application/streamingmedia"
    ,".sst","application/vnd.ms-pki.certstore"
    ,".stl","application/vnd.ms-pki.stl"
    ,".stm","text/html"
    ,".sty","application/x-sty"
    ,".svg","text/xml"
    ,".swf","application/x-shockwave-flash"
    ,".tdf","application/x-tdf"
    ,".tg4","application/x-tg4"
    ,".tga","application/x-tga"
    ,".tif","image/tiff"
    ,".tif","application/x-tif"
    ,".tiff","image/tiff"
    ,".tld","text/xml"
    ,".top","drawing/x-top"
    ,".torrent","application/x-bittorrent"
    ,".tsd","text/xml"
    ,".txt","text/plain"
    ,".uin","application/x-icq"
    ,".uls","text/iuls"
    ,".vcf","text/x-vcard"
    ,".vda","application/x-vda"
    ,".vdx","application/vnd.visio"
    ,".vml","text/xml"
    ,".vpg","application/x-vpeg005"
    ,".vsd","application/vnd.visio"
    ,".vsd","application/x-vsd"
    ,".vss","application/vnd.visio"
    ,".vst","application/vnd.visio"
    ,".vst","application/x-vst"
    ,".vsw","application/vnd.visio"
    ,".vsx","application/vnd.visio"
    ,".vtx","application/vnd.visio"
    ,".vxml","text/xml"
    ,".wav","audio/wav"
    ,".wax","audio/x-ms-wax"
    ,".wb1","application/x-wb1"
    ,".wb2","application/x-wb2"
    ,".wb3","application/x-wb3"
    ,".wbmp","image/vnd.wap.wbmp"
    ,".wiz","application/msword"
    ,".wk3","application/x-wk3"
    ,".wk4","application/x-wk4"
    ,".wkq","application/x-wkq"
    ,".wks","application/x-wks"
    ,".wm","video/x-ms-wm"
    ,".wma","audio/x-ms-wma"
    ,".wmd","application/x-ms-wmd"
    ,".wmf","application/x-wmf"
    ,".wml","text/vnd.wap.wml"
    ,".wmv","video/x-ms-wmv"
    ,".wmx","video/x-ms-wmx"
    ,".wmz","application/x-ms-wmz"
    ,".wp6","application/x-wp6"
    ,".wpd","application/x-wpd"
    ,".wpg","application/x-wpg"
    ,".wpl","application/vnd.ms-wpl"
    ,".wq1","application/x-wq1"
    ,".wr1","application/x-wr1"
    ,".wri","application/x-wri"
    ,".wrk","application/x-wrk"
    ,".ws","application/x-ws"
    ,".ws2","application/x-ws"
    ,".wsc","text/scriptlet"
    ,".wsdl","text/xml"
    ,".wvx","video/x-ms-wvx"
    ,".xdp","application/vnd.adobe.xdp"
    ,".xdr","text/xml"
    ,".xfd","application/vnd.adobe.xfd"
    ,".xfdf","application/vnd.adobe.xfdf"
    ,".xhtml","text/html"
    ,".xls","application/vnd.ms-excel"
    ,".xls","application/x-xls"
    ,".xlw","application/x-xlw"
    ,".xml","text/xml"
    ,".xpl","audio/scpls"
    ,".xq","text/xml"
    ,".xql","text/xml"
    ,".xquery","text/xml"
    ,".xsd","text/xml"
    ,".xsl","text/xml"
    ,".xslt","text/xml"
    ,".xwd","application/x-xwd"
    ,".x_b","application/x-x_b"
    ,".x_t","application/x-x_t"
};

static const char * _get_content_type(char *filename)
{
    int i = 0;
    int size = sizeof(g_ext_to_content_type)/sizeof(g_ext_to_content_type[0]);

    char *ext = filename;
    char * slash = strrchr(filename, '/');
    if(slash)
    {
        slash++;
    }
    else
    {
        slash = filename;
    }

    ext = strrchr(filename, '.');
    if(!ext)
    {
        return "application/octet-stream";
    }

    for(; i < size; i += 2)
    {
        if(!strcmp(ext, g_ext_to_content_type[i]))
        {
            return g_ext_to_content_type[i+1];
        }
    }

    return "application/octet-stream";
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , m_nam(this)
    , m_reply(0)
    , m_request(0)
    , m_file(0)
{
    setupGUI();
}

Widget::~Widget()
{
    if(m_file)
    {
        m_file->close();
        delete m_file;
    }

    if(m_reply)
    {
        m_reply->disconnect(this);
        m_reply->abort();
        delete m_reply;
    }
}

void Widget::setupGUI()
{
    QVBoxLayout * mainLayout = new QVBoxLayout();
    setLayout(mainLayout);

    m_headerValueGroup = new QGroupBox(tr("http header"), this);
    QGridLayout * headerValueLayout = new QGridLayout();
    headerValueLayout->setColumnStretch(1, 1);
    m_headerValueLabel = new QLabel(tr("header value:"), this);
    m_headerValueEdit = new QLineEdit(this);
    m_headerKeyLabel = new QLabel(tr("header key:"), this);
    m_headerKeyEdit = new QLineEdit(this);
    m_addHttpHeaderValueButton = new QPushButton(tr("Add"), this);
    connect(m_addHttpHeaderValueButton, SIGNAL(clicked()), this, SLOT(onAddHttpHeaderValue()));
    headerValueLayout->addWidget(m_headerKeyLabel, 0, 0, Qt::AlignRight | Qt::AlignVCenter);
    headerValueLayout->addWidget(m_headerKeyEdit, 0, 1);
    headerValueLayout->addWidget(m_headerValueLabel, 1, 0, Qt::AlignRight | Qt::AlignVCenter);
    headerValueLayout->addWidget(m_headerValueEdit, 1, 1);
    headerValueLayout->addWidget(m_addHttpHeaderValueButton, 2, 0, 1, 2, Qt::AlignRight | Qt::AlignVCenter);
    m_headerValueGroup->setLayout(headerValueLayout);

    mainLayout->addWidget(m_headerValueGroup);

    m_paramGroup = new QGroupBox(tr("base parameters"), this);
    QGridLayout * paramLayout = new QGridLayout();
    paramLayout->setColumnStretch(1, 1);
    m_urlLabel = new QLabel(tr("url:"), this);
    m_urlEdit = new QLineEdit(this);
    m_methodLabel = new QLabel(tr("method:"), this);
    m_methodCombo = new QComboBox(this);
    m_methodCombo->setEditable(false);
    m_methodCombo->addItem("HEAD");
    m_methodCombo->addItem("GET");
    m_methodCombo->addItem("POST");
    m_methodCombo->addItem("DELETE");
    //m_methodCombo->setCurrentIndex(0);
    connect(m_methodCombo, SIGNAL(currentTextChanged(QString))
            , this, SLOT(onMethodChanged(QString)));
    m_startButton = new QPushButton(tr("start"), this);
    connect(m_startButton, SIGNAL(clicked()), this, SLOT(onStart()));

    paramLayout->addWidget(m_urlLabel, 0, 0, Qt::AlignRight | Qt::AlignVCenter);
    paramLayout->addWidget(m_urlEdit, 0, 1);
    paramLayout->addWidget(m_methodLabel, 1, 0, Qt::AlignRight | Qt::AlignVCenter);
    paramLayout->addWidget(m_methodCombo, 1, 1, Qt::AlignRight | Qt::AlignVCenter);
    paramLayout->addWidget(m_startButton, 2, 0, 1, 2, Qt::AlignRight | Qt::AlignVCenter);
    m_paramGroup->setLayout(paramLayout);

    mainLayout->addWidget(m_paramGroup);

    //
    m_stateGroup = new QGroupBox(tr("state"), this);
    QVBoxLayout * stateLayout = new QVBoxLayout();
    m_progress = new QProgressBar();
    m_progress->setRange(0, 100);
    m_progress->setValue(0);
    stateLayout->addWidget(m_progress);

    m_stateText = new QTextEdit(this);
    m_stateText->setReadOnly(true);
    stateLayout->addWidget(m_stateText, 1);
    m_stateGroup->setLayout(stateLayout);

    mainLayout->addWidget(m_stateGroup, 2);
}

void Widget::disableControls()
{
    m_addHttpHeaderValueButton->setDisabled(true);
    m_startButton->setDisabled(true);
    m_headerKeyEdit->setDisabled(true);
    m_headerValueEdit->setDisabled(true);
    m_urlEdit->setDisabled(true);
    m_methodCombo->setDisabled(true);
}

void Widget::enableControls()
{
    m_addHttpHeaderValueButton->setEnabled(true);
    m_startButton->setEnabled(true);
    m_headerKeyEdit->setEnabled(true);
    m_headerValueEdit->setEnabled(true);
    m_urlEdit->setEnabled(true);
    m_methodCombo->setEnabled(true);
}

QString Widget::requestString(QNetworkRequest *req)
{
    QString joinedHeader;
    QVariant variant = req->header(QNetworkRequest::ContentTypeHeader);  //根据传入的枚举类型，返回对应的网络报头
    if(variant.isValid())
    {
        joinedHeader += "content-type: ";
        joinedHeader += variant.toString();
        joinedHeader += "\n";
    }

    variant = req->header(QNetworkRequest::UserAgentHeader);  //返回HTTP客户端发送的用户代理头
    if(variant.isValid())
    {
        joinedHeader += "user-agent: ";
        joinedHeader += variant.toString();
        joinedHeader += "\n";
    }

    QList<QByteArray> headerList = req->rawHeaderList();  //返回在这个网络请求中设置的原始标题列表
    int count = headerList.size();
    QByteArray value;
    for(int i = 0; i < count; i++)
    {
        const QByteArray &tag = headerList.at(i);
        value = req->rawHeader(tag);  //返回对应头的原始形式
        joinedHeader += QString("%1: %2\n").arg(tag.data()).arg(value.data());   //加入头列表和值
    }

    return joinedHeader;
}

QString Widget::responseString(QNetworkReply *reply)
{
    QString joinedHeader;
    QVariant variant = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);  //返回代码相关的属性：本输入表示“收到HTTP服务器的HTTP状态代码”
    if(variant.isValid())
    {
        joinedHeader = QString("STATUS: %1\n").arg(variant.toInt());
    }

    QList<QByteArray> headerList = reply->rawHeaderList();
    int count = headerList.size();
    QByteArray value;
    for(int i = 0; i < count; i++)
    {
        const QByteArray &tag = headerList.at(i);
        value = reply->rawHeader(tag);
        joinedHeader += QString("%1: %2\n").arg(tag.data()).arg(value.data());  //加入头列表和值
    }

    return joinedHeader;
}

void Widget::onAddHttpHeaderValue()
{
    if(!m_request)
    {
        m_request = new QNetworkRequest();
    }
    QString header = m_headerKeyEdit->text();
    if(header.compare("user-agent", Qt::CaseInsensitive) == 0)
    {
        m_request->setHeader( QNetworkRequest::UserAgentHeader,
                              m_headerValueEdit->text());
    }
    m_request->setRawHeader(header.toLatin1()
                                  , m_headerValueEdit->text().toLatin1());
    m_stateText->setText(requestString(m_request));
}

void Widget::onStart()
{   //根据界面传入的URL初始化了一个QNetworkRequest对象
    disableControls();
    m_stateText->clear();
    m_progress->setValue(0);

    if(!m_request)
    {
        m_request = new QNetworkRequest();
    }

    QString strURL = m_urlEdit->text();
    QUrl qurl(strURL);
    QString httpMethod = m_methodCombo->currentText();

    m_request->setUrl(qurl);
    //根据用户选择的HTTP方法，调用对应的函数，返回一个QnetworkReply对象
    if(httpMethod == "GET")
    {
        QString errorString;
        if(!openFile(true, errorString))
        {
            QMessageBox::warning(this, tr("Save File Error")
                                 , errorString
                                 , QMessageBox::Ok);
            resetState();
            return;
        }
        m_reply = m_nam.get(*m_request);
    }
    else if(httpMethod == "POST")
    {
        QString errorString;
        if(!openFile(false, errorString))
        {
            QMessageBox::warning(this, tr("Upload File Error")
                                 , errorString
                                 , QMessageBox::Ok);
            resetState();
            return;
        }
        m_reply = m_nam.post(*m_request, m_file);
        m_request->setHeader(QNetworkRequest::ContentTypeHeader,
                             _get_content_type(m_strFilePath.toLatin1().data()));
    }
    else if(httpMethod == "HEAD")
    {
        m_reply = m_nam.head(*m_request);
    }
    else if(httpMethod == "DELETE")
    {
        m_reply = m_nam.deleteResource(*m_request);
    }
    else
    {
        QMessageBox::information(this, tr("information")
                             , tr("Please select a Method!")
                             , QMessageBox::Ok);
        resetState();
        return;
    }
    //根据返回的对象，我们可以连接到它的各种信号以便获取网络操作的不同状态
    connect(m_reply, SIGNAL(finished()), this, SLOT(onFinished())); //这个信号在在一个网络应答结束时会发出
    connect(m_reply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));  //m_reply继承父QIODevice的readyRead()信号
    connect(m_reply, SIGNAL(downloadProgress(qint64,qint64)),
            this, SLOT(onDownloadProgress(qint64,qint64)));
    connect(m_reply, SIGNAL(uploadProgress(qint64,qint64)),
            this, SLOT(onUploadProgress(qint64,qint64)));
    connect(m_reply, SIGNAL(metaDataChanged()), this, SLOT(onMetaDataChanged()));  //这个信号在收到服务器元数据时会触发
    //元数据：内如之外的数据，如内容长度(Content-Length)、内容类型(Content-Type)等。一般收到内容第一个字节前就解析出来了
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onFinished()));

    m_stateText->setText(requestString(m_request));

    m_stateText->append("\n===========response==========\n");
}


void Widget::onMethodChanged(const QString &method)
{
    if(method == "GET")
    {
        // open file for save
        m_strFilePath = QFileDialog::getSaveFileName(this, tr("save file"));
    }
    else if(method == "POST")
    {
        // open file for upload
        m_strFilePath = QFileDialog::getOpenFileName(this, tr("upload file"));
    }
}

void Widget::onMetaDataChanged()
{
    m_stateText->setText(responseString(m_reply));
}

void Widget::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    if(bytesTotal > 0)
    {
        int value = (bytesReceived * 100) / bytesTotal;
        m_progress->setValue(value);
    }
}

void Widget::onUploadProgress(qint64 bytesSent, qint64 bytesTotal)
{
    if(bytesTotal > 0)
    {
        int value = (bytesSent * 100) / bytesTotal;
        m_progress->setValue(value);
    }
}

void Widget::onReadyRead()
{
    QByteArray data = m_reply->readAll();  //读取所有已下载的数据
    m_stateText->append(QString("read %1 bytes\n").arg(data.length()));
    if(m_file)   //写到文件里面
    {
        m_file->write(data);
    }
}

void Widget::onFinished()
{
    QString strState = m_reply->error() == QNetworkReply::NoError ? "success" : m_reply->errorString();
    m_stateText->append(QString("\nhttp request done - %1\n")
                        .arg(strState));
    m_stateText->append("\n-------\n");
    resetState();
}

void Widget::resetState()
{
    if(m_file)
    {
        m_file->close();
        delete m_file;
        m_file = 0;
    }
    if(m_request)
    {
        delete m_request;
        m_request = 0;
    }
    if(m_reply)
    {
        m_reply->disconnect(this);
        m_reply->deleteLater();
        m_reply = 0;
    }

    enableControls();
}

bool Widget::openFile(bool save, QString &errorString)
{
    if(m_strFilePath.isEmpty())
    {
        errorString = "No File Selected";
        return false;
    }
    if(m_file)
    {
        delete m_file;
        m_file = 0;
    }
    m_file = new QFile(m_strFilePath);
    if(!m_file->open(save ? QFile::WriteOnly : QFile::ReadOnly))
    {
        errorString = m_file->errorString();
        delete m_file;
        m_file = 0;
        return false;
    }
    return true;
}
