[ComponentEditorProps(category: "GameMode Component", description: "Allows VIPs to use the Admin queue bypass, but strips their admin powers upon connection.")]
class VIPRoleRestrictorComponentClass : SCR_BaseGameModeComponentClass {}

class VIPRoleRestrictorComponent : SCR_BaseGameModeComponent
{
    // Список GUID ваших VIP игроков (должны совпадать с блоком admins в ServerConfig.json)
    protected ref array<string> m_aVipGuids = {
        "28a51194-b5ab-40d4-8be6-ada0cfe9f98d"
    };

    // Метод срабатывает на сервере сразу после успешного подключения игрока
    override void OnPlayerConnected(int playerId)
    {
        super.OnPlayerConnected(playerId);

        BackendApi backendApi = GetGame().GetBackendApi();
        PlayerManager playerManager = GetGame().GetPlayerManager();
        
        if (!backendApi || !playerManager)
            return;

        // Получаем 36-значный GUID подключившегося VIP
        string playerGuid = backendApi.GetPlayerIdentityId(playerId);

        // Проверяем, есть ли зашедший VIP-админ в нашем списке
        if (m_aVipGuids.Contains(playerGuid))
        {
            // Официальный метод API Arma Reforger для снятия конкретной роли с игрока.
            // Стираем флаг ADMINISTRATOR, понижая роль пользователя до обычной.
            playerManager.ClearPlayerRole(playerId, EPlayerRole.ADMINISTRATOR);
            
            // Исправлено: убран проблемный аргумент LogKind_NORMAL
            Print(string.Format("[VIP System] VIP Player (ID: %1) bypassed queue. Admin rights stripped via ClearPlayerRole.", playerId));
        }
    }
}
