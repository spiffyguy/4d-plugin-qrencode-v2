/* --------------------------------------------------------------------------------
 #
 #  4DPlugin-qrencode.cpp
 #	source generated by 4D Plugin Wizard
 #	Project : qrencode
 #	author : miyako
 #	2019/10/10
 #  
 # --------------------------------------------------------------------------------*/

#include "4DPlugin-qrencode.h"

#pragma mark -

void PluginMain(PA_long32 selector, PA_PluginParameters params) {
    
	try
	{
        switch(selector)
        {
			// --- qrencode
            
			case 1 :
				qrencode(params);
				break;
			case 2 :
				qrcode_array(params);
				break;

        }

	}
	catch(...)
	{

	}
}

#pragma mark -

void qrencode(PA_PluginParameters params) {
    
    output_type_t type = QR_OUTPUT_PNG;
    int margin = 0;
    int size = 3;
    int dpi = 72;
    int version = 1;
    QRencodeMode mode = QR_MODE_8;
    QRecLevel level = QR_ECLEVEL_L;
    int micro = 0;
    int swiss = 0;
    
    PA_ObjectRef returnValue = PA_CreateObject();
    PA_ObjectRef options = PA_GetObjectParameter(params, 2);
    
    if(options) {

        level = (QRecLevel)(int)ob_get_n(options, L"level");
        level = ((level <= QR_ECLEVEL_H) & (level >= QR_ECLEVEL_L)) ? level : QR_ECLEVEL_L;
        
        int _mode = (QRencodeMode)(int)ob_get_n(options, L"mode");
        
        if(_mode & QR_Mode_Kanji) {
            mode  = QR_MODE_KANJI;
        }else{
            mode  = QR_MODE_8;
        }
        
        if(_mode & QR_Mode_Micro) {
            micro  = 1;
        }else{
            micro  = 0;
        }

        if(_mode & QR_Mode_Swiss) {
            swiss  = 1;
        }else{
            swiss  = 0;
        }
        
        type = (output_type_t)(int)ob_get_n(options, L"format");
        type = type == QR_OUTPUT_SVG ? QR_OUTPUT_SVG : type == QR_OUTPUT_PNG ? QR_OUTPUT_PNG : QR_OUTPUT_TEXT;
        
        margin = (int)ob_get_n(options, L"margin");
        margin = margin < 0 ? 0 : margin;

        size = (int)ob_get_n(options, L"size");
        size = size > 0 ? size : 3;

        dpi = (int)ob_get_n(options, L"dpi");
        dpi = dpi > 0 ? dpi : 72;
        
        version = (int)ob_get_n(options, L"version");
        version = version > 0 ? version : 1;
        
    }
    
    C_TEXT data;
    data.setUTF16String(PA_GetStringParameter(params, 1));

    unsigned int len = 0;
    
    uint32_t dataSize = (data.getUTF16Length() * sizeof(PA_Unichar) * 2)+ sizeof(uint8_t);
    std::vector<char> buf(dataSize);
    
    PA_4DCharSet encoding;
    
    switch (mode)
    {
        case QR_MODE_KANJI:
        encoding = eVTC_SHIFT_JIS;
        break;
        default:
        encoding = eVTC_UTF_8;
        break;
    }
    
    if (swiss)
    {
        encoding = eVTC_ISO_8859_1;
        mode = QR_MODE_AN;
    }
    
    len = PA_ConvertCharsetToCharset((char *)data.getUTF16StringPtr(),
                                     data.getUTF16Length() * sizeof(PA_Unichar),
                                     eVTC_UTF_16,
                                     (char *)&buf[0],
                                     dataSize,
                                     encoding);
    
    QRcode *qr = NULL;
    
    if(micro){
        
        if(mode == QR_MODE_KANJI){
            
            qr = QRcode_encodeStringMQR((const char *)&buf[0],
                                        version,
                                        level,
                                        mode,
                                        1);
            
        }else{
            
            qr = QRcode_encodeDataMQR((int)len,
                                      (const unsigned char *)&buf[0],
                                      version,
                                      level);
        }
        
    }else{
        
        if(mode == QR_MODE_KANJI){
            
            qr = QRcode_encodeString((const char *)&buf[0],
                                     version,
                                     level,
                                     mode,
                                     1);
            
        }else{
            
            qr = QRcode_encodeData((int)len,
                                   (const unsigned char *)&buf[0],
                                   version,
                                   level);
            
        }
        
    }
    
    if(qr){
        
        switch(type){
            case QR_OUTPUT_PNG:
            toPNG(qr, margin, size, dpi, returnValue);
            break;
            
            case QR_OUTPUT_SVG:
            toSVG(qr, margin, size, dpi, returnValue);
            break;

            case QR_OUTPUT_TEXT:
            toTEXT(qr, margin, size, dpi, returnValue);
            break;
        }
        
        QRcode_free(qr);
        
    }
    
    PA_ReturnObject(params, returnValue);    
}

void qrcode_array(PA_PluginParameters params) {
    
    output_type_t type = QR_OUTPUT_PNG;
    int margin = 0;
    int size = 3;
    int dpi = 72;
    int version = 1;
    QRencodeMode mode = QR_MODE_8;
    QRecLevel level = QR_ECLEVEL_L;
    int micro = 0;
    int swiss = 0;
    
    PA_CollectionRef returnValue = PA_CreateCollection();
    PA_ObjectRef options = PA_GetObjectParameter(params, 2);
    
    if(options) {
        
        level = (QRecLevel)(int)ob_get_n(options, L"level");
        level = ((level <= QR_ECLEVEL_H) & (level >= QR_ECLEVEL_L)) ? level : QR_ECLEVEL_L;
        
        int _mode = (QRencodeMode)(int)ob_get_n(options, L"mode");
        
        if(_mode & QR_Mode_Kanji) {
            mode  = QR_MODE_KANJI;
        }else{
            mode  = QR_MODE_8;
        }
        
        if(_mode & QR_Mode_Micro) {
            micro  = 1;
        }else{
            micro  = 0;
        }
        
        if(_mode & QR_Mode_Swiss) {
            swiss  = 1;
        }else{
            swiss  = 0;
        }
        
        type = (output_type_t)(int)ob_get_n(options, L"format");
        type = type == QR_OUTPUT_SVG ? QR_OUTPUT_SVG : type == QR_OUTPUT_PNG ? QR_OUTPUT_PNG : QR_OUTPUT_TEXT;
        
        margin = (int)ob_get_n(options, L"margin");
        margin = margin < 0 ? 0 : margin;
        
        size = (int)ob_get_n(options, L"size");
        size = size > 0 ? size : 3;
        
        dpi = (int)ob_get_n(options, L"dpi");
        dpi = dpi > 0 ? dpi : 72;
        
        version = (int)ob_get_n(options, L"version");
        version = version > 0 ? version : 1;
        
    }
    
    C_TEXT data;
    data.setUTF16String(PA_GetStringParameter(params, 1));

    unsigned int len = 0;
    
    uint32_t dataSize = (data.getUTF16Length() * sizeof(PA_Unichar) * 2)+ sizeof(uint8_t);
    std::vector<char> buf(dataSize);
    
    PA_4DCharSet encoding;
    
    switch (mode)
    {
        case QR_MODE_KANJI:
        encoding = eVTC_SHIFT_JIS;
        break;
        default:
        encoding = eVTC_UTF_8;
        break;
    }
    
    len = PA_ConvertCharsetToCharset((char *)data.getUTF16StringPtr(),
                                     data.getUTF16Length() * sizeof(PA_Unichar),
                                     eVTC_UTF_16,
                                     (char *)&buf[0],
                                     dataSize,
                                     encoding);
    
    QRcode_List *qrl = NULL;
    
    if (mode == QR_MODE_KANJI)
    {
        qrl = QRcode_encodeStringStructured((const char *)&buf[0],
                                            version,
                                            level,
                                            mode,
                                            1);
    }else
    {
        qrl = QRcode_encodeDataStructured((int)len,
                                          (const unsigned char *)&buf[0],
                                          version,
                                          level);
    }
    
    if (qrl)
    {
        int count = QRcode_List_size(qrl);
        QRcode *qr;
        for (unsigned int i = 0; i < count; ++i)
        {
            if(qrl)
            {
                qr = qrl->code;
                
                switch (type)
                {
                    case QR_OUTPUT_PNG:
                    toPNGs(qr, margin, size, dpi, i, returnValue);
                    break;
                    
                    case QR_OUTPUT_SVG:
                    toSVGs(qr, margin, size, dpi, i, returnValue);
                    break;

                    case QR_OUTPUT_TEXT:
                    toTEXTs(qr, margin, size, dpi, i, returnValue);
                    break;
                }
                
                qrl = qrl->next;
            }
            else
            {
                break;
            }
        }
        QRcode_List_free(qrl);
    }
    
    PA_ReturnCollection(params, returnValue);
}

void toSVGs(QRcode *qr, int margin, int size, int dpi, int pos, PA_CollectionRef c) {
    
    margin = margin * size;
    
    char _size[33];
    sprintf(_size, "%d", size);
    
    char _width[33];
    sprintf(_width, "%d", margin + (qr->width * size) + margin);
    
    char _dpi[33];
    sprintf(_dpi, "%d", dpi);
    
    char _margin[33];
    sprintf(_margin, "%d", margin);
    
    char _x[33];
    char _y[33];
    
    std::string svg;
    
    svg += "<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n";
    svg += "<svg width=\"100%\" height=\"100%\" viewBox=\"0 0 ";
    svg += _width;
    svg += " ";
    svg += _width;
    svg += "\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:ns4d=\"http://www.4d.com\" ns4d:DPI=\"";
    svg += _dpi;
    svg += "\">\n";
    svg += "<g shape-rendering=\"crispEdges\" stroke-width=\"0\" stroke=\"none\" transform=\"translate(";
    svg += _margin;
    svg += ",";
    svg += _margin;
    svg += ")\">\n";
    
    unsigned char *p;
    int x, y = 0, i, j;
    
    p = qr->data;
    
    for(i = 0; i < qr->width; ++i)
    {
        //        PA_YieldAbsolute();
        x = 0;
        sprintf(_y, "%d", y);
        
        for(j = 0; j < qr->width; ++j)
        {
            sprintf(_x, "%d", x);
            
            if(*p&1)
            {
                svg += "<rect fill=\"black\" stroke=\"black\" height=\"";
                svg += _size;
                svg += "\" width=\"";
                svg += _size;
                svg += "\" ";
            }else{
                svg += "<rect fill=\"white\" stroke=\"white\" height=\"";
                svg += _size;
                svg += "\" width=\"";
                svg += _size;
                svg += "\" ";
            }
            
            svg += "x=\"";
            svg += _x;
            svg += "\" ";
            svg += "y=\"";
            svg += _y;
            svg += "\" />\n";
            
            p++;
            x = x + size;
            
        }
        y = y + size;
    }
    
    svg += "</g>\n";
    svg += "</svg>\n";
    
    if(c) {
        PA_ObjectRef o = PA_CreateObject();
        
        CUTF8String _svg((const uint8_t *)svg.c_str());
        ob_set_s(o, L"data", (const char *)_svg.c_str());
        
        PA_Picture p = PA_CreatePicture((void *)svg.c_str(), (PA_long32)svg.size());
        PA_Variable v = PA_CreateVariable(eVK_Picture);
        PA_SetPictureVariable(&v, p);/* we let go, so don't dispose */
        
        CUTF16String ukey;
        json_wconv(L"image", &ukey);
        PA_Unistring key = PA_CreateUnistring((PA_Unichar *)ukey.c_str());
        
        PA_SetObjectProperty(o, &key, v);
        
        PA_DisposeUnistring(&key);/* we still own it, so dispose */
        PA_ClearVariable(&v);
        
        v = PA_CreateVariable(eVK_Object);
        PA_SetObjectVariable(&v, o);/* we let go, so don't dispose */
        
        PA_SetCollectionElement(c, pos, v);
        PA_ClearVariable(&v);
    }
}

void toPNGs(QRcode *qr, int margin, int size, int dpi, int pos, PA_CollectionRef c) {
    
    unsigned int fg_color[4] = {0, 0, 0, 255};
    unsigned int bg_color[4] = {255, 255, 255, 255};
    
    png_structp png_ptr;
    png_infop info_ptr;
    png_colorp palette;
    png_byte alpha_values[2];
    unsigned char *row, *p, *q;
    int x, y, xx, yy, bit;
    int realwidth;
    
    realwidth = (qr->width + margin * 2) * size;
    row = (unsigned char *)malloc((realwidth + 7) / 8);
    if(row != NULL) {
        
        png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if(png_ptr != NULL) {
            
            info_ptr = png_create_info_struct(png_ptr);
            if(info_ptr != NULL) {
                
                if(setjmp(png_jmpbuf(png_ptr))) {
                    png_destroy_write_struct(&png_ptr, &info_ptr);
                }else{
                    
                    palette = (png_colorp) malloc(sizeof(png_color) * 2);
                    if(palette != NULL) {
                        
                        palette[0].red   = fg_color[0];
                        palette[0].green = fg_color[1];
                        palette[0].blue  = fg_color[2];
                        palette[1].red   = bg_color[0];
                        palette[1].green = bg_color[1];
                        palette[1].blue  = bg_color[2];
                        alpha_values[0] = fg_color[3];
                        alpha_values[1] = bg_color[3];
                        png_set_PLTE(png_ptr, info_ptr, palette, 2);
                        png_set_tRNS(png_ptr, info_ptr, alpha_values, 2, NULL);
                        
                        C_BLOB png;
                        
                        png_set_write_fn(png_ptr, (png_voidp)&png, write_data_fn, output_flush_fn);
                        
                        png_set_IHDR(png_ptr, info_ptr,
                                     realwidth, realwidth,
                                     1,
                                     PNG_COLOR_TYPE_PALETTE,
                                     PNG_INTERLACE_NONE,
                                     PNG_COMPRESSION_TYPE_DEFAULT,
                                     PNG_FILTER_TYPE_DEFAULT);
                        png_set_pHYs(png_ptr, info_ptr,
                                     dpi * INCHES_PER_METER,
                                     dpi * INCHES_PER_METER,
                                     PNG_RESOLUTION_METER);
                        
                        png_write_info(png_ptr, info_ptr);
                        
                        /* top margin */
                        memset(row, 0xff, (realwidth + 7) / 8);
                        for(y=0; y<margin * size; y++) {
                            png_write_row(png_ptr, row);
                        }
                        
                        /* data */
                        p = qr->data;
                        for(y=0; y<qr->width; y++) {
                            //                            PA_YieldAbsolute();
                            bit = 7;
                            memset(row, 0xff, (realwidth + 7) / 8);
                            q = row;
                            q += margin * size / 8;
                            bit = 7 - (margin * size % 8);
                            for(x=0; x<qr->width; x++) {
                                for(xx=0; xx<size; xx++) {
                                    *q ^= (*p & 1) << bit;
                                    bit--;
                                    if(bit < 0) {
                                        q++;
                                        bit = 7;
                                    }
                                }
                                p++;
                            }
                            for(yy=0; yy<size; yy++) {
                                png_write_row(png_ptr, row);
                            }
                        }
                        
                        /* bottom margin */
                        memset(row, 0xff, (realwidth + 7) / 8);
                        for(y=0; y<margin * size; y++) {
                            png_write_row(png_ptr, row);
                        }
                        
                        png_write_end(png_ptr, info_ptr);
                        png_destroy_write_struct(&png_ptr, &info_ptr);
                        
                        free(row);
                        free(palette);
                        
                        if(c) {
                            PA_ObjectRef o = PA_CreateObject();
                            
                            C_TEXT dump;
                            png.toB64Text(&dump);
                            
                            CUTF16String u;
                            dump.copyUTF16String(&u);
                            ob_set_a(o, L"data", &u);
                            
                            PA_Picture p = PA_CreatePicture((void *)png.getBytesPtr(), png.getBytesLength());
                            PA_Variable v = PA_CreateVariable(eVK_Picture);
                            PA_SetPictureVariable(&v, p);/* we let go, so don't dispose */
                            
                            CUTF16String ukey;
                            json_wconv(L"image", &ukey);
                            PA_Unistring key = PA_CreateUnistring((PA_Unichar *)ukey.c_str());
                            
                            PA_SetObjectProperty(o, &key, v);
                            
                            PA_DisposeUnistring(&key);/* we still own it, so dispose */
                            PA_ClearVariable(&v);
                            
                            v = PA_CreateVariable(eVK_Object);
                            PA_SetObjectVariable(&v, o);/* we let go, so don't dispose */
                            
                            PA_SetCollectionElement(c, pos, v);
                            PA_ClearVariable(&v);
                        }
                    }
                }
            }
        }
    }
}

void toTEXTs(QRcode *qr, int margin, int size, int dpi, int pos, PA_CollectionRef c) {
    
    margin = margin * size;
    
    char _size[33];
    sprintf(_size, "%d", size);
    
    char _width[33];
    sprintf(_width, "%d", margin + (qr->width * size) + margin);
    
    char _dpi[33];
    sprintf(_dpi, "%d", dpi);
    
    char _margin[33];
    sprintf(_margin, "%d", margin);
    
    char _x[33];
    char _y[33];
    
    std::string textResponse;
    
    unsigned char *p;
    int x, y = 0, i, j;
    
    p = qr->data;
    
    for(i = 0; i < qr->width; ++i)
    {
        //        PA_YieldAbsolute();
        x = 0;
        sprintf(_y, "%d", y);
        
        for(j = 0; j < qr->width; ++j)
        {
            sprintf(_x, "%d", x);
            
            if(*p&1)
            {
                textResponse += "1";
            }else{
                textResponse += "0";
            }
            
            p++;
            x = x + size;
            
        }

        textResponse += "\n";

        y = y + size;
    }
    
    if(c) {
        PA_ObjectRef o = PA_CreateObject();
        
        CUTF8String _textResponse((const uint8_t *)textResponse.c_str());
        ob_set_s(o, L"data", (const char *)_textResponse.c_str());
        
        PA_Picture p = PA_CreatePicture(0,0); // Empty
        PA_Variable v = PA_CreateVariable(eVK_Picture);
        PA_SetPictureVariable(&v, p);/* we let go, so don't dispose */
        
        CUTF16String ukey;
        json_wconv(L"image", &ukey);
        PA_Unistring key = PA_CreateUnistring((PA_Unichar *)ukey.c_str());
        
        PA_SetObjectProperty(o, &key, v);
        
        PA_DisposeUnistring(&key);/* we still own it, so dispose */
        PA_ClearVariable(&v);
        
        v = PA_CreateVariable(eVK_Object);
        PA_SetObjectVariable(&v, o);/* we let go, so don't dispose */
        
        PA_SetCollectionElement(c, pos, v);
        PA_ClearVariable(&v);
    }
}

void write_data_fn(png_structp png_ptr, png_bytep buf, png_size_t size) {
    C_BLOB *blob = (C_BLOB *)png_get_io_ptr(png_ptr);
    blob->addBytes((const uint8_t *)buf, (uint32_t)size);
}

void output_flush_fn(png_structp png_ptr)
{
    
}

void toSVG(QRcode *qr, int margin, int size, int dpi, PA_ObjectRef o) {
    
    margin = margin * size;
    
    char _size[33];
    sprintf(_size, "%d", size);
    
    char _width[33];
    sprintf(_width, "%d", margin + (qr->width * size) + margin);
    
    char _dpi[33];
    sprintf(_dpi, "%d", dpi);
    
    char _margin[33];
    sprintf(_margin, "%d", margin);
    
    char _x[33];
    char _y[33];
    
    std::string svg;
    
    svg += "<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n";
    svg += "<svg width=\"100%\" height=\"100%\" viewBox=\"0 0 ";
    svg += _width;
    svg += " ";
    svg += _width;
    svg += "\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:ns4d=\"http://www.4d.com\" ns4d:DPI=\"";
    svg += _dpi;
    svg += "\">\n";
    svg += "<g shape-rendering=\"crispEdges\" stroke-width=\"0\" stroke=\"none\" transform=\"translate(";
    svg += _margin;
    svg += ",";
    svg += _margin;
    svg += ")\">\n";
    
    unsigned char *p;
    int x, y = 0, i, j;
    
    p = qr->data;
    
    for(i = 0; i < qr->width; ++i)
    {
        //        PA_YieldAbsolute();
        x = 0;
        sprintf(_y, "%d", y);
        
        for(j = 0; j < qr->width; ++j)
        {
            sprintf(_x, "%d", x);
            
            if(*p&1)
            {
                svg += "<rect fill=\"black\" stroke=\"black\" height=\"";
                svg += _size;
                svg += "\" width=\"";
                svg += _size;
                svg += "\" ";
            }else{
                svg += "<rect fill=\"white\" stroke=\"white\" height=\"";
                svg += _size;
                svg += "\" width=\"";
                svg += _size;
                svg += "\" ";
            }
            
            svg += "x=\"";
            svg += _x;
            svg += "\" ";
            svg += "y=\"";
            svg += _y;
            svg += "\" />\n";
            
            p++;
            x = x + size;
            
        }
        y = y + size;
    }
    
    svg += "</g>\n";
    svg += "</svg>\n";
    
    if(o) {
        
        CUTF8String _svg((const uint8_t *)svg.c_str());
        ob_set_s(o, L"data", (const char *)_svg.c_str());
        
        PA_Picture p = PA_CreatePicture((void *)svg.c_str(), (PA_long32)svg.size());
        PA_Variable v = PA_CreateVariable(eVK_Picture);
        PA_SetPictureVariable(&v, p);/* we let go, so don't dispose */
        
        CUTF16String ukey;
        json_wconv(L"image", &ukey);
        PA_Unistring key = PA_CreateUnistring((PA_Unichar *)ukey.c_str());
        
        PA_SetObjectProperty(o, &key, v);
        
        PA_DisposeUnistring(&key);/* we still own it, so dispose */
        PA_ClearVariable(&v);
    }
}

void toPNG(QRcode *qr, int margin, int size, int dpi, PA_ObjectRef o) {
    
    unsigned int fg_color[4] = {0, 0, 0, 255};
    unsigned int bg_color[4] = {255, 255, 255, 255};
    
    png_structp png_ptr;
    png_infop info_ptr;
    png_colorp palette;
    png_byte alpha_values[2];
    unsigned char *row, *p, *q;
    int x, y, xx, yy, bit;
    int realwidth;
    
    realwidth = (qr->width + margin * 2) * size;
    row = (unsigned char *)malloc((realwidth + 7) / 8);
    if(row != NULL) {
        
        png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if(png_ptr != NULL) {
            
            info_ptr = png_create_info_struct(png_ptr);
            if(info_ptr != NULL) {
                
                if(setjmp(png_jmpbuf(png_ptr))) {
                    png_destroy_write_struct(&png_ptr, &info_ptr);
                }else{
                    
                    palette = (png_colorp) malloc(sizeof(png_color) * 2);
                    if(palette != NULL) {
                        
                        palette[0].red   = fg_color[0];
                        palette[0].green = fg_color[1];
                        palette[0].blue  = fg_color[2];
                        palette[1].red   = bg_color[0];
                        palette[1].green = bg_color[1];
                        palette[1].blue  = bg_color[2];
                        alpha_values[0] = fg_color[3];
                        alpha_values[1] = bg_color[3];
                        png_set_PLTE(png_ptr, info_ptr, palette, 2);
                        png_set_tRNS(png_ptr, info_ptr, alpha_values, 2, NULL);
                        
                        C_BLOB png;
                        
                        png_set_write_fn(png_ptr, (png_voidp)&png, write_data_fn, output_flush_fn);
                        
                        png_set_IHDR(png_ptr, info_ptr,
                                     realwidth, realwidth,
                                     1,
                                     PNG_COLOR_TYPE_PALETTE,
                                     PNG_INTERLACE_NONE,
                                     PNG_COMPRESSION_TYPE_DEFAULT,
                                     PNG_FILTER_TYPE_DEFAULT);
                        png_set_pHYs(png_ptr, info_ptr,
                                     dpi * INCHES_PER_METER,
                                     dpi * INCHES_PER_METER,
                                     PNG_RESOLUTION_METER);
                        
                        png_write_info(png_ptr, info_ptr);
                        
                        /* top margin */
                        memset(row, 0xff, (realwidth + 7) / 8);
                        for(y=0; y<margin * size; y++) {
                            png_write_row(png_ptr, row);
                        }
                        
                        /* data */
                        p = qr->data;
                        for(y=0; y<qr->width; y++) {
                            //                            PA_YieldAbsolute();
                            bit = 7;
                            memset(row, 0xff, (realwidth + 7) / 8);
                            q = row;
                            q += margin * size / 8;
                            bit = 7 - (margin * size % 8);
                            for(x=0; x<qr->width; x++) {
                                for(xx=0; xx<size; xx++) {
                                    *q ^= (*p & 1) << bit;
                                    bit--;
                                    if(bit < 0) {
                                        q++;
                                        bit = 7;
                                    }
                                }
                                p++;
                            }
                            for(yy=0; yy<size; yy++) {
                                png_write_row(png_ptr, row);
                            }
                        }
                        
                        /* bottom margin */
                        memset(row, 0xff, (realwidth + 7) / 8);
                        for(y=0; y<margin * size; y++) {
                            png_write_row(png_ptr, row);
                        }
                        
                        png_write_end(png_ptr, info_ptr);
                        png_destroy_write_struct(&png_ptr, &info_ptr);
                        
                        free(row);
                        free(palette);
                        
                        if(o) {
                            
                            C_TEXT dump;
                            png.toB64Text(&dump);
                            
                            CUTF16String u;
                            dump.copyUTF16String(&u);
                            ob_set_a(o, L"data", &u);
                            
                            PA_Picture p = PA_CreatePicture((void *)png.getBytesPtr(), png.getBytesLength());
                            PA_Variable v = PA_CreateVariable(eVK_Picture);
                            PA_SetPictureVariable(&v, p);/* we let go, so don't dispose */

                            CUTF16String ukey;
                            json_wconv(L"image", &ukey);
                            PA_Unistring key = PA_CreateUnistring((PA_Unichar *)ukey.c_str());
                            
                            PA_SetObjectProperty(o, &key, v);
                            
                            PA_DisposeUnistring(&key);/* we still own it, so dispose */
                            PA_ClearVariable(&v);
                        }
                    }
                }
            }
        }
    }
}

void toTEXT(QRcode *qr, int margin, int size, int dpi, PA_ObjectRef o) {
    
    margin = margin * size;
    
    char _size[33];
    sprintf(_size, "%d", size);
    
    char _width[33];
    sprintf(_width, "%d", margin + (qr->width * size) + margin);
    
    char _dpi[33];
    sprintf(_dpi, "%d", dpi);
    
    char _margin[33];
    sprintf(_margin, "%d", margin);
    
    char _x[33];
    char _y[33];
    
    std::string textResponse;
    
    unsigned char *p;
    int x, y = 0, i, j;
    
    p = qr->data;
    
    for(i = 0; i < qr->width; ++i)
    {
        //        PA_YieldAbsolute();
        x = 0;
        sprintf(_y, "%d", y);
        
        for(j = 0; j < qr->width; ++j)
        {
            sprintf(_x, "%d", x);
            
            if(*p&1)
            {
                textResponse += "1";

            }else{
                textResponse += "0";

            }
            
            
            p++;
            x = x + size;
            
        }

        textResponse += "\n";
        
        y = y + size;
    }
    
    if(o) {
        
        CUTF8String _textResponse((const uint8_t *)textResponse.c_str());
        ob_set_s(o, L"data", (const char *)_textResponse.c_str());
        
        PA_Picture p = PA_CreatePicture(0,0);
        PA_Variable v = PA_CreateVariable(eVK_Picture);
        PA_SetPictureVariable(&v, p);/* we let go, so don't dispose */
        
        CUTF16String ukey;
        json_wconv(L"image", &ukey);
        PA_Unistring key = PA_CreateUnistring((PA_Unichar *)ukey.c_str());
        
        PA_SetObjectProperty(o, &key, v);
        
        PA_DisposeUnistring(&key);/* we still own it, so dispose */
        PA_ClearVariable(&v);
    }
}