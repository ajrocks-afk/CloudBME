// ================= WIFI =================
const char* ssid = "WIFI_NAME_HERE";
const char* password = "WIFI_PASSWORD_HERE";;

// ================= AWS =================
const char* awsEndpoint = "AWS_ENDPOINT_HERE";
const int awsPort = "AWS_PROT_HERE";
const char* publishTopic = "bme/data";

// ================= CERTIFICATES =================
static const char AWS_ROOT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
#CERTIFICATE_HERE
-----END CERTIFICATE-----

)EOF";

static const char AWS_CERT[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
#CERTIFICATE_HERE
-----END CERTIFICATE-----

)EOF";

static const char AWS_PRIVATE_KEY[] PROGMEM = R"EOF(
-----BEGIN RSA PRIVATE KEY-----
#CERTIFICATE_PRIVATE KEY_HERE
-----END RSA PRIVATE KEY-----

)EOF";
