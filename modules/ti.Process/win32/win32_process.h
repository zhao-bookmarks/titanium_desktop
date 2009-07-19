/**
 * Appcelerator Titanium - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2009 Appcelerator, Inc. All Rights Reserved.
 */
 
#ifndef _WIN32_PROCESS_H_
#define _WIN32_PROCESS_H_

#include <sstream>
#include "win32_pipe.h"
#include "../process.h"

#undef stdin
#undef stdout
#undef stderr

namespace ti
{
	class Win32Process : public Process
	{
	public:
		Win32Process();
		virtual ~Win32Process();

		virtual AutoPipe GetNativeStdin() { return nativeIn; }
		virtual AutoPipe GetNativeStdout() { return nativeOut; }
		virtual AutoPipe GetNativeStderr() { return nativeErr; }
		
		virtual int GetPID();
		virtual void Terminate();
		virtual void Kill();
		virtual void SendSignal(int signal);
		virtual void ForkAndExec();
		virtual void MonitorAsync();
		virtual std::string MonitorSync();
		virtual int Wait();
		virtual std::string ArgumentsToString();
		void ReadCallback(const ValueList& args, SharedValue result);
		
	protected:
		std::string ArgListToString(SharedKList argList);
		
		Poco::Thread exitMonitorThread;
		Poco::RunnableAdapter<Win32Process>* exitMonitorAdapter;
		AutoPtr<Win32Pipe> nativeIn, nativeOut, nativeErr;
		Poco::Mutex mutex;
		
		Poco::Mutex processOutputMutex;
		std::vector<AutoBlob> processOutput;
		
		int pid;
		HANDLE process;
		
		Logger* logger;
	};
}

#endif
