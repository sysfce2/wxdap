#ifndef GDBHANDLER_HPP
#define GDBHANDLER_HPP

#include "DebuggerHandler.hpp"
#include <unordered_map>

class GdbHandler : public DebuggerHandler
{
    size_t m_commandCounter = 0;
    vector<string> m_debugeeArgs;
    string m_stdout;
    string m_stderr;
    unordered_map<string, function<dap::ProtocolMessage::Ptr_t(const string&)>> m_handlersMap;

protected:
    string NextSequence();
    void OnOutput(string& inbuffer);
    dap::ProtocolMessage::Ptr_t CreateOutputEvent(const string& buffer);
    dap::ProtocolMessage::Ptr_t OnBreakpointUpdate(const string& buffer);
    static string ParseErrorMessage(const string& buffer);
    
public:
    GdbHandler();
    virtual ~GdbHandler();

public:
    /// The IDE initiated a launch request
    void OnLaunchRequest(dap::ProtocolMessage::Ptr_t message) override;
    /// Configuration Done request has arrived
    void OnConfigurationDoneRequest(dap::ProtocolMessage::Ptr_t message) override;
    /// Set breakpoints
    void OnSetBreakpoints(dap::ProtocolMessage::Ptr_t message) override;
    /// Load the debuggee process into gdb
    void StartDebugger(const string& debuggerExecutable, const string& wd) override;
    /// Process raw stdout string
    void OnDebuggerStdout(const string& message) override;
    /// Process raw stderr string
    void OnDebuggerStderr(const string& message) override;
};

#endif // GDBHANDLER_HPP