# Set Up AWS Lambda C Runtime: You'll need to download and set up the AWS Lambda C runtime. This involves getting the necessary libraries and setting up your development environment to build Lambda functions in C.
# Write Your Lambda Function: The function will need to process incoming requests, check the Authorization header, and respond accordingly.
# Deploy Your Function: Package your function and any dependencies, and then deploy it to AWS Lambda.

# The function checks if the Authorization header is present and not equal to "Bearer"

#include <aws/lambda-runtime/runtime.h>
#include <json-c/json.h>
#include <string.h>

static invocation_response my_handler(invocation_request const& request)
{
    json_object *parsed_json;
    parsed_json = json_tokener_parse(request.payload);
    
    json_object *headers;
    json_object_object_get_ex(parsed_json, "headers", &headers);

    json_object *authHeader;
    json_object_object_get_ex(headers, "Authorization", &authHeader);
    
    const char* authValue = json_object_get_string(authHeader);

    if (authValue != NULL && strcmp(authValue, "Bearer") != 0) {
        // Authorization header is present and not equal to 'Bearer'
        return invocation_response::success("{\"message\":\"Unauthorized\"}", "application/json");
    } else {
        // Authorization header is missing or equals 'Bearer'
        return invocation_response::success("{\"message\":\"Authorized\"}", "application/json");
    }
}

int main()
{
    run_handler(my_handler);
    return 0;
}
