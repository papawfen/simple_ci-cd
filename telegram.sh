#!/bin/bash
TELEGRAM_BOT_TOKEN="5574450908:AAGix7lr1v1VJe8bhP3FvAEh4Qj0QFLJ9xM"
TELEGRAM_USER_ID="788048508"
TIME=1
URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"
TEXT="Deploy status: $1%0A%0AProject:+$CI_PROJECT_NAME%0AURL:+$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID/%0ABranch:+$CI_COMMIT_REF_SLUG"
curl -s --max-time $TIME -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null