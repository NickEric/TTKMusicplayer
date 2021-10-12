#include <QSettings>
#include <math.h>
#include "stereoplugin.h"

StereoPlugin *StereoPlugin::m_instance = nullptr;

StereoPlugin::StereoPlugin()
    : Effect()
{
    m_instance = this;
    QSettings settings(Qmmp::configFile(), QSettings::IniFormat);
    m_intensity = settings.value("Stereo/intensity", 1.0).toDouble();
}

StereoPlugin::~StereoPlugin()
{
    m_instance = nullptr;
}

void StereoPlugin::applyEffect(Buffer *b)
{
    if(channels() != 2)
    {
        return;
    }

    m_mutex.lock();
    float *data = b->data;
    for(size_t i = 0; i < b->samples; i += 2)
    {
        m_avg = (data[i] + data[i + 1]) / 2;
        m_ldiff = data[i] - m_avg;
        m_rdiff = data[i + 1] - m_avg;

        m_offset = m_avg + m_ldiff * m_intensity;
        data[i] = qBound(-1.0, m_offset, 1.0);
        m_offset = m_avg + m_rdiff * m_intensity;
        data[i + 1] = qBound(-1.0, m_offset, 1.0);
    }
    m_mutex.unlock();
}

void StereoPlugin::setIntensity(double level)
{
    m_mutex.lock();
    m_intensity = level;
    m_mutex.unlock();
}

StereoPlugin* StereoPlugin::instance()
{
    return m_instance;
}
