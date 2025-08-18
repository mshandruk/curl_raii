#pragma once

namespace curl_raii
{
    inline CURL *CurlRAIIAdapterImpl::get() const
    {
        return curl_raii_.get();
    }
}
