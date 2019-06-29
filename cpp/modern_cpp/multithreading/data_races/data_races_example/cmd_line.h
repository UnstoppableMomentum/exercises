#ifndef CMD_LINE_H
#define CMD_LINE_H

class TestOptions;
bool parseCommandLine(TestOptions& options, bool bPrintArgs, int argc, char **argv);

#endif // CMD_LINE_H
