#include "xsfhelper.h"
#include "xsfreader.h"

#define SAMPLE_BUF_SIZE     1024

XSFHelper::XSFHelper(const QString &path)
    : m_path(path)
{
    m_info = (decode_info*)calloc(sizeof(decode_info), 1);
}

XSFHelper::~XSFHelper()
{
    deinit();
}

void XSFHelper::deinit()
{
    delete m_info->input;
    free(m_info);
}

void XSFHelper::metaOnly(bool meta)
{
    m_info->meta = meta;
}

bool XSFHelper::initialize()
{
    QFile file(m_path);
    if(!file.open(QFile::ReadOnly))
    {
        qWarning("XSFHelper: open file failed");
        file.close();
        return false;
    }

    const qint64 size = file.size();
    file.close();

    m_info->input = XSFReader::makeReader(m_path);
    if(!m_info->input)
    {
        qWarning("XSFHelper: load file suffix error");
        return false;
    }

    if(!m_info->input->load(QmmpPrintable(m_path), m_info->meta))
    {
       qWarning("XSFHelper: load error");
       return false;
    }

    m_info->bitrate = size * 8.0 / totalTime() + 1.0f;
    return true;
}

qint64 XSFHelper::totalTime() const
{
    return m_info->input->length();
}

void XSFHelper::seek(qint64 time)
{
    m_info->input->seek(time);
}

int XSFHelper::bitrate() const
{
    return m_info->bitrate;
}

int XSFHelper::sampleRate() const
{
    return 44100;
}

int XSFHelper::channels() const
{
    return 2;
}

int XSFHelper::bitsPerSample() const
{
    return 16;
}

qint64 XSFHelper::read(unsigned char *data, qint64)
{
    return m_info->input->read((short*)data, SAMPLE_BUF_SIZE) * 4;
}

QMap<Qmmp::MetaData, QString> XSFHelper::readMetaData() const
{
    QMap<Qmmp::MetaData, QString> metaData;
    if(!m_info->input)
    {
        return metaData;
    }

    const file_meta meta(m_info->input->get_meta_map());
    for(auto itr = meta.begin(); itr != meta.end(); ++itr)
    {
        if(itr->first == "title")
            metaData.insert(Qmmp::TITLE, QString::fromStdString(itr->second));
        else if(itr->first == "artist")
            metaData.insert(Qmmp::ARTIST, QString::fromStdString(itr->second));
        else if(itr->first == "album")
            metaData.insert(Qmmp::ALBUM, QString::fromStdString(itr->second));
        else if(itr->first == "year")
            metaData.insert(Qmmp::YEAR, QString::fromStdString(itr->second));
        else if(itr->first == "genre")
            metaData.insert(Qmmp::GENRE, QString::fromStdString(itr->second));
        else if(itr->first == "copyright")
            metaData.insert(Qmmp::COMMENT, QString::fromStdString(itr->second));
    }
    return metaData;
}
