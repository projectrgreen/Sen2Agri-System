#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "requestparamsexecutioninfos.h"

#include "logger.hpp"

RequestParamsExecutionInfos::RequestParamsExecutionInfos()
    : RequestParamsBase(PROCESSOR_EXECUTION_INFO_MSG)
{

}

bool RequestParamsExecutionInfos::ParseMessage(const QByteArray &message)
{
    QJsonParseError err;
    QJsonDocument document = QJsonDocument::fromJson(message, &err);
    if(err.error != QJsonParseError::NoError || !document.isObject()) {
        Logger::error(QStringLiteral("Invalid JSON message: %1").arg(QString::fromUtf8(message)));
        return false;
    }

    const auto &obj = document.object();
    m_strJobName = obj["JOB_NAME"].toString();
    m_strMsgType = obj["MSG_TYPE"].toString();
    // no longer used
    m_strLogMsg = obj["LOG_MSG"].toString();
    m_strExecTime = obj["EXEC_TIME"].toString();
    return true;
}

bool RequestParamsExecutionInfos::IsExecutionStarted()
{
    if(m_strMsgType == "STARTED")
        return true;
    return false;
}


bool RequestParamsExecutionInfos::IsExecutionEnded()
{
    if(m_strMsgType == "ENDED")
        return true;
    return false;
}

bool RequestParamsExecutionInfos::IsLogMsg()
{
    if(m_strMsgType == "LOG")
        return true;
    return false;
}

const QString& RequestParamsExecutionInfos::GetJobName() const
{
    return m_strJobName;
}

const QString& RequestParamsExecutionInfos::GetLogMsg() const
{
    return m_strLogMsg;
}

const QString& RequestParamsExecutionInfos::GetExecutionTime() const
{
    return m_strExecTime;
}

const QString& RequestParamsExecutionInfos::GetStdOutText() const
{
    return m_strStdOutText;
}

const QString& RequestParamsExecutionInfos::GetStdErrText() const
{
    return m_strStdErrText;
}
