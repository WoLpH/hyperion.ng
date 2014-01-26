#pragma once

// stl includes
#include <string>

// Qt includes
#include <QColor>
#include <QImage>
#include <QTcpSocket>
#include <QMap>

// hyperion util
#include <utils/Image.h>
#include <utils/ColorRgb.h>

// jsoncpp includes
#include <message.pb.h>

///
/// Connection class to setup an connection to the hyperion server and execute commands
///
class ProtoConnection
{
public:
	///
	/// Constructor
	///
	/// @param address The address of the Hyperion server (for example "192.168.0.32:19444)
	///
	ProtoConnection(const std::string & address);

	///
	/// Destructor
	///
	~ProtoConnection();

	///
	/// Set all leds to the specified color
	///
	/// @param color The color
	/// @param priority The priority
	/// @param duration The duration in milliseconds
	///
	void setColor(const ColorRgb & color, int priority, int duration = 1);

	///
	/// Set the leds according to the given image (assume the image is stretched to the display size)
	///
	/// @param image The image
	/// @param priority The priority
	/// @param duration The duration in milliseconds
	///
	void setImage(const Image<ColorRgb> & image, int priority, int duration = -1);

	///
	/// Clear the given priority channel
	///
	/// @param priority The priority
	///
	void clear(int priority);

	///
	/// Clear all priority channels
	///
	void clearAll();

private:
	///
	/// Send a command message and receive its reply
	///
	/// @param message The message to send
	///
	/// @return The returned reply
	///
	proto::HyperionReply sendMessage(const proto::HyperionRequest & message);

	///
	/// Parse a reply message
	///
	/// @param reply The received reply
	///
	/// @return true if the reply indicates success
	///
	bool parseReply(const proto::HyperionReply & reply);

private:
	/// The TCP-Socket with the connection to the server
	QTcpSocket _socket;
};