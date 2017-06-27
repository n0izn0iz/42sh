const child_process = require('child_process')
const fileName = 'testraw'
const valgrindErrorCode = 242
const failure = 1
const success = 0
const green   = "\033[32m";
const red	  = "\033[31m";
const stopColor = "\033[0m";
var result_status = success;
const lineReader = require('readline').createInterface({
	terminal: false,
	input: require('fs').createReadStream(fileName)
})

function exec_cmd(shell, cmd)
{
	var result = {}
	try {
		result.output = child_process.execFileSync(shell, ['-c', cmd], {encoding: 'ascii', stdio: 'pipe'})
		result.status = 0
	} catch (exception) {
		result.status = exception.status
	}
	return (result)
}

function exec_valgrind(cmd)
{
	var result = {}
	try {
		result.output = child_process.execFileSync('valgrind', ['--leak-check=full', '--error-exitcode=' + valgrindErrorCode, './42sh', '-c', cmd], {encoding: 'ascii', stdio: 'pipe'})
		result.status = 0
	} catch (exception) {
		result.status = exception.status
	}
	return (result)
}

function exec_line(line) {
	const ourShell = './42sh'
	const refShell = 'sh'
	var testResult = {
		command: line,
		our: exec_cmd(ourShell, line),
		ref: exec_cmd(refShell, line),
		valgrind: exec_valgrind(line)
	}
	testResult.statusError = (testResult.our.status !== testResult.ref.status)
	testResult.outputError = (testResult.our.output !== testResult.ref.output)
	testResult.valgrindError = (testResult.valgrind.status == valgrindErrorCode)
	if (testResult.statusError || testResult.outputError || testResult.valgrindError)
	{
		if (!testResult.valgrindError)
			result_status = failure;
		console.log(red + '[KO]' + stopColor + ' ' + line)
	}
	else
		console.log(green + '[OK]' + stopColor + ' ' + line)
	if (testResult.statusError)
		console.log('Status diff: ' + testResult.our.status + ' (our) != ' + testResult.ref.status + ' (ref)')
	if (testResult.outputError)
	{
		console.log('Output diff:\nOur:')
		console.log(testResult.our.output + '\nRef:\n' + testResult.ref.status)
	}
	if (testResult.valgrindError)
		console.log('Memory leak(s)!')
}

lineReader.on('line', function (line) {
	if (line != "" && line[0] != '#')
		exec_line(line)
})
process.exit(result_status)
