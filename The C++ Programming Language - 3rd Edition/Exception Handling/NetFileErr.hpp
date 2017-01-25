
#pragma once

class NetworkErr {
	// ...
};

class FileSystemErr {
	// ...
};

class NetFileErr : public NetworkErr, public FileSystemErr {
	// ...
};

